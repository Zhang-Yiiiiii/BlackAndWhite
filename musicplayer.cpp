#include "MusicPlayer.h"
#include <QStyle>
#include <QTime>
#include "MusicPlayer.h"
#include "qpainter.h"
#include <QStyle>
#include <QTime>
#include <QCoreApplication>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>

MusicPlayer::MusicPlayer(QWidget *parent)
    : QDialog(parent), m_userLoaded(false)
{
    setFixedSize(300, 300);
    setWindowTitle("音乐");

    // 初始化多媒体组件
    m_player = new QMediaPlayer(this);
    m_output = new QAudioOutput(this);
    m_player->setAudioOutput(m_output);
    m_output->setVolume(0.5);  // 初始音量设为50%

    // 创建界面组件
    m_backgroundLabel = new QLabel(this);
    //m_backgroundLabel->setPixmap(QPixmap(":/image/listenMusic.jpg"));
    m_slider = new QSlider(Qt::Horizontal, this);
    m_timeLabel = new QLabel("00:00 / 00:00", this);

    // 控制按钮
    m_playButton = new QPushButton(this);
    m_openButton = new QPushButton("打开音乐", this);
    m_loopButton = new QPushButton("循环: 开", this);

    // 音量控制组件
    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeLabel = new QLabel("50%", this);
    m_muteButton = new QPushButton(this);

    // 设置组件参数
    //m_slider->setEnabled(false);
    m_volumeSlider->setRange(0, 100);  // 音量范围0-100%
    m_volumeSlider->setValue(50);      // 初始音量位置
    updatePlayPauseIcon();
    m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // 连接信号槽
    connect(m_player, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayer::handleMediaStatus);
    connect(m_slider, &QSlider::sliderMoved, this, &MusicPlayer::setPositionByClick);
    connect(m_playButton, &QPushButton::clicked, this, &MusicPlayer::togglePlayPause);
    connect(m_openButton, &QPushButton::clicked, this, &MusicPlayer::openFile);
    connect(m_loopButton, &QPushButton::clicked, this, [this]
    {
        m_loop = !m_loop;
        m_loopButton->setText(m_loop ? "循环: 开" : "循环: 关");
    });

    //媒体加载状态监控
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status)
    {
        if(status == QMediaPlayer::LoadedMedia)    // 媒体加载完成后更新时长
        {
            updateDuration(m_player->duration());
        }
    });

    // 音量控制信号槽
    connect(m_volumeSlider, &QSlider::valueChanged, this, [this](int value)
    {
        m_isMuted = false;
        m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
        float volume = value / 100.0f;
        m_output->setVolume(volume);
        m_volumeLabel->setText(QString::number(value) + "%");

    });

    connect(m_slider, &QSlider::sliderPressed, this, [ = ]()
    {
        m_isSeeking = true;  // 标记拖动开始
    });

    connect(m_slider, &QSlider::sliderReleased, this, [ = ]()
    {
        m_player->setPosition(m_slider->value());
        m_isSeeking = false; // 清除拖动标记
    });

    connect(m_muteButton, &QPushButton::clicked, this, &MusicPlayer::toggleMute);

    // 布局设置
    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(m_openButton);
    controlLayout->addWidget(m_playButton);
    controlLayout->addWidget(m_loopButton);

    QHBoxLayout *volumeLayout = new QHBoxLayout;
    volumeLayout->addWidget(m_muteButton);
    volumeLayout->addWidget(m_volumeSlider);
    volumeLayout->addWidget(m_volumeLabel);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 1. 添加顶部空白区域（使用QSpacerItem）
    mainLayout->addSpacerItem(new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding));

    // 2. 添加背景标签（居中显示）
    mainLayout->addWidget(m_backgroundLabel, 0, Qt::AlignCenter);

    // 3. 添加其他控件
    mainLayout->addWidget(m_slider);
    mainLayout->addWidget(m_timeLabel);
    mainLayout->addLayout(volumeLayout);
    mainLayout->addLayout(controlLayout);

    // 设置布局边距（使背景区域更明显）
    mainLayout->setContentsMargins(40, 10, 40, 20);  // 左, 上, 右, 下

    loadDefaultMusic(); //加载默认音乐

    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));  //图标
}

// 文件选择功能
void MusicPlayer::openFile()
{
    QStringList filters;
    filters << "MP3文件 (*.mp3)"
            << "WAV文件 (*.wav)"
            << "OGG文件 (*.ogg)"
            << "所有文件 (*.*)";

    QString path = QFileDialog::getOpenFileName(this,
                   "选择音乐文件",
                   QStandardPaths::writableLocation(QStandardPaths::MusicLocation),
                   filters.join(";;"));

    if (!path.isEmpty())
    {
        QFileInfo fileInfo(path);
        setWindowTitle(fileInfo.fileName() + " - 音乐播放器");

        m_player->setSource(QUrl::fromLocalFile(path));

        if(m_player->playbackState() != QMediaPlayer::PlayingState)
        {
            m_player->play();
        }

        m_userLoaded = true;
    }
}

// 进度更新
void MusicPlayer::updatePosition(qint64 pos)
{
    if(!m_isSeeking && m_slider->maximum() > 0)
    {
        m_slider->blockSignals(true);
        m_slider->setValue(static_cast<int>(pos));
        m_slider->blockSignals(false);
    }

    QTime currentTime(0, 0, 0);
    currentTime = currentTime.addMSecs(static_cast<int>(pos));
    QString format = currentTime.hour() > 0 ? "hh:mm:ss" : "mm:ss";
    m_timeLabel->setText(currentTime.toString(format) + " / " + m_totalTime);
}

// 时长更新
void MusicPlayer::updateDuration(qint64 dur)
{
    m_slider->setRange(0, static_cast<int>(dur));
    m_slider->setEnabled(dur > 0);

    if(dur > 0)
    {
        QTime totalTime(0, 0, 0);
        totalTime = totalTime.addMSecs(static_cast<int>(dur));
        m_totalTime = totalTime.toString(totalTime.hour() > 0 ? "hh:mm:ss" : "mm:ss");
    }
    else
    {
        m_totalTime = "--:--";
    }

    updatePosition(m_player->position());
}

// 媒体状态处理
void MusicPlayer::handleMediaStatus(QMediaPlayer::MediaStatus status)
{
    switch(status)
    {
        case QMediaPlayer::EndOfMedia:
            if(m_loop)
            {
                m_player->setPosition(0);
                m_player->play();
            }
            else    //更改播放图标
            {
                m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            }

            break;

        case QMediaPlayer::InvalidMedia:
            QMessageBox::warning(this, "错误", "不支持的媒体格式或损坏文件");
            break;

        case QMediaPlayer::NoMedia:
            if(!m_userLoaded)
            {
                loadDefaultMusic();
            }

            break;

        default:
            break;
    }
}

void MusicPlayer::paintEvent(QPaintEvent* event)
{

    Q_UNUSED(event);
    QPainter painter(this);

    QPixmap bg(":/image/musicBackground.png");

    if (bg.isNull())
    {
        return;
    }

    QSize widgetSize = size();
    QSize pixmapSize = bg.size();
    pixmapSize.scale(widgetSize, Qt::KeepAspectRatio); // 等比例缩放

    QPoint topLeft((widgetSize.width() - pixmapSize.width()) / 2,
                   (widgetSize.height() - pixmapSize.height()) / 2);

    QRect targetRect(topLeft, pixmapSize);

    painter.drawPixmap(targetRect, bg);
}

// 进度跳转
void MusicPlayer::setPositionByClick(int pos)
{
    if(pos >= 0 && pos <= m_slider->maximum())
    {
        m_player->setPosition(pos);
    }
}

// 静音切换
void MusicPlayer::toggleMute()
{
    m_isMuted = !m_isMuted;

    if(m_isMuted)
    {
        m_output->setVolume(0);
        m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolumeMuted));
    }
    else
    {
        m_output->setVolume(m_volumeSlider->value() / 100.0);
        qDebug() << m_volumeSlider->value();
        m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    }
}

//加载默认音乐函数
void MusicPlayer::loadDefaultMusic()
{
    if (!m_userLoaded)
    {
        // 检查资源文件是否存在
        if (QFile(":/music/music.mp3").exists())
        {
            m_player->setSource(QUrl("qrc:/music/music.mp3"));
            m_player->play();  // 关键修正：添加自动播放
        }
        else
        {
            qWarning() << "Default music file not found in resources";
        }
    }
}

// 播放/暂停功能
void MusicPlayer::togglePlayPause()
{
    // 如果没有加载任何媒体，先尝试打开文件
    if (m_player->source().isEmpty())
    {
        openFile();
        return;
    }

    switch(m_player->playbackState())
    {
        case QMediaPlayer::PlayingState:
            m_player->pause();
            break;

        case QMediaPlayer::PausedState:
        case QMediaPlayer::StoppedState:
            m_player->play();
            break;
    }

    updatePlayPauseIcon();
}

// 按钮状态更新
void MusicPlayer::updatePlayPauseIcon()
{
    bool isPlaying = (m_player->playbackState() == QMediaPlayer::PlayingState);

    QStyle::StandardPixmap icon = isPlaying ?
                                  QStyle::SP_MediaPause :
                                  QStyle::SP_MediaPlay;

    m_playButton->setIcon(style()->standardIcon(icon));

}

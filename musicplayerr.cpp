#include "musicplayerr.h"
#include "ui_musicplayerr.h"

#include <QAudioOutput>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMovie>
#include <QVideoWidget>

const QSize WindowSize(1020, 720);

MusicPlayerr::MusicPlayerr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicPlayerr)
{
    ui->setupUi(this);

    setFixedSize(WindowSize);
    setWindowTitle("音乐");
    setBackground(":/image/musicBackgnd.png");

    ui->groupBox->hide();
    ui->musicList->move(QPoint(this->width(), 0));  //默认隐藏

    m_player = new QMediaPlayer(this);
    m_output = new QAudioOutput(this);

    m_output->setVolume(0.5);
    m_player->setAudioOutput(m_output);
    m_player->play();

    initBtns();

    ui->volumeSlider->setRange(0, 100);  // 音量范围0-100%
    ui->volumeSlider->setValue(50);      // 初始音量位置

    m_dir = QString("D:\\QtProjects\\BlackAndWhiteBlock\\music");   //默认位置
    loadDir(m_dir);

    connect(m_player, &QMediaPlayer::positionChanged, this, &MusicPlayerr::updatePosition);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MusicPlayerr::updateDuration);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MusicPlayerr::handleMediaStatus);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MusicPlayerr::updateVolume);
    connect(ui->progressSlider, &QSlider::valueChanged, this, &MusicPlayerr::setPositionByClick);
}

MusicPlayerr::~MusicPlayerr()
{
    delete ui;
}

void MusicPlayerr::setBackground(const QString fileName)
{
    QPixmap pix(fileName);
    QSize windowSize = this->size();
    QPixmap scalePix = pix.scaled(windowSize);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePix));

    this->setPalette(palette);
}

void MusicPlayerr::setBtnStyle(QPushButton *btn, QString fileName)
{
    btn->setFixedSize(50, 50);
    btn->setStyleSheet("background-color: rgba(255,255,255,0.2); ");
    btn->setIcon(QIcon(fileName));
}

void MusicPlayerr::initBtns()
{
    setBtnStyle(ui->prevBtn, ":/icon/prevMusic.png");
    setBtnStyle(ui->playBtn, ":/icon/pause.png");
    setBtnStyle(ui->nextBtn, ":/icon/nextMusic.png");
    setBtnStyle(ui->listBtn, ":/icon/list.png");
    setBtnStyle(ui->modeBtn, ":/icon/order.png");
    setBtnStyle(ui->openFile, ":/icon/upload.png");

    ui->musicList->setStyleSheet(
        "QListWidget {"
        "    border: none;"
        "    border-radius: 5px;"
        "    background-color: rgba(255, 255, 255, 0.4);"
        "}"
    );

    connect(ui->prevBtn, &QPushButton::clicked, this, &MusicPlayerr::onPrevBtnclicked);
    connect(ui->playBtn, &QPushButton::clicked, this, &MusicPlayerr::onPlayBtnclicked);
    connect(ui->modeBtn, &QPushButton::clicked, this, &MusicPlayerr::onModeBtnclicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &MusicPlayerr::onNextBtnclicked);
    connect(ui->listBtn, &QPushButton::clicked, this, &MusicPlayerr::onListBtnclicked);
    connect(ui->openFile, &QPushButton::clicked, this, &MusicPlayerr::openFile);

}

void MusicPlayerr::loadDir(const QString &fileName)
{
    if (fileName.trimmed().isEmpty())
    {
        QMessageBox::warning(this, "错误", "目录路径为空！");
        return;
    }

    QDir dir(fileName);
    qDebug() << "music file:" << fileName;

    if (!dir.exists())
    {
        QMessageBox::warning(this, "警告", "目录不存在！");
        return;
    }

    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    ui->musicList->clear();

    for (const QFileInfo &e : fileList)
    {
        if (e.suffix().toLower() == "mp3")
        {
            ui->musicList->addItem(e.baseName());
        }
    }

    // 文件夹中没有 mp3 文件时避免崩溃
    if (ui->musicList->count() == 0)
    {
        QMessageBox::information(this, "提示", "该目录下没有找到 MP3 音乐文件。");
        return;
    }

    m_dir = fileName;

    ui->musicList->setCurrentRow(0);
    startMusic();
}

void MusicPlayerr::startMusic()
{
    QString musicName(ui->musicList->currentItem()->text());

    QString path = m_dir + "\\" + musicName + ".mp3";
    qDebug() << path;
    m_player->setSource(QUrl::fromLocalFile(path));

    m_player->play();
}

void MusicPlayerr::showList()
{
    QPropertyAnimation ani(ui->groupBox, "pos");
    ani.setDuration(1000);
    ani.setStartValue(QPoint(this->width(), 10));
    ani.setEndValue(QPoint(this->width() - ui->groupBox->width(), 10));
    ani.start();

    QEventLoop lp;
    connect(&ani, &QPropertyAnimation::finished, &lp, &QEventLoop::quit);
    lp.exec();

}

void MusicPlayerr::hideList()
{
    QPropertyAnimation ani(ui->groupBox, "pos");
    ani.setDuration(1000);
    ani.setStartValue(QPoint(this->width() - ui->groupBox->width(), 10));
    ani.setEndValue(QPoint(this->width(), 10));

    ani.start();

    QEventLoop lp;
    connect(&ani, &QPropertyAnimation::finished, &lp, &QEventLoop::quit);
    lp.exec();
}

void MusicPlayerr::onPrevBtnclicked()
{
    //当前行
    int currentRow = ui->musicList->currentRow();

    int prevRow = 0;

    if(m_mode == ORDER_MODE)
    {
        prevRow = (currentRow - 1);

        if(prevRow < 0)
        {
            prevRow = ui->musicList->count() - 1;
        }
    }
    else if(m_mode == RANDOM_MODE)
    {
        do
        {
            prevRow = rand() % ui->musicList->count();
        } while(prevRow == currentRow && ui->musicList->count() >= 2);
    }
    else
    {
        prevRow = currentRow;
    }

    ui->musicList->setCurrentRow(prevRow);
    startMusic();
}

void MusicPlayerr::onPlayBtnclicked()
{
    if(ui->musicList->count() == 0)
    {
        QMessageBox::warning(this, "提醒", "请先加载音乐");
        return;
    }

    QMediaPlayer::PlaybackState state = m_player->playbackState();

    if(state == QMediaPlayer::PlayingState)
    {
        m_player->pause();
        ui->playBtn->setIcon(QIcon(":/icon/play.png"));
    }
    else if(state == QMediaPlayer::StoppedState || state == QMediaPlayer::PausedState)
    {
        m_player->play();
        ui->playBtn->setIcon(QIcon(":/icon/pause.png"));
    }
}

void MusicPlayerr::onModeBtnclicked()
{
    if(m_mode == ORDER_MODE)
    {
        m_mode = RANDOM_MODE;

        ui->modeBtn->setIcon(QIcon(":/icon/random.png"));

    }
    else if(m_mode == RANDOM_MODE)
    {
        m_mode = CIRCLE_MODE;
        ui->modeBtn->setIcon(QIcon(":/icon/circle.png"));

    }
    else
    {
        m_mode = ORDER_MODE;
        ui->modeBtn->setIcon(QIcon(":/icon/order.png"));

    }
}

void MusicPlayerr::onNextBtnclicked()
{
    //当前行
    int currentRow = ui->musicList->currentRow();

    int nextRow = 0;

    if(m_mode == ORDER_MODE)
    {
        nextRow = (currentRow + 1) % ui->musicList->count();
    }
    else if(m_mode == RANDOM_MODE)
    {
        do
        {
            nextRow = rand() % ui->musicList->count();
        } while(nextRow == currentRow && ui->musicList->count() >= 2);
    }
    else
    {
        nextRow = currentRow;
    }

    ui->musicList->setCurrentRow(nextRow);
    startMusic();
}

void MusicPlayerr::onListBtnclicked()
{
    m_isShowList = !m_isShowList;

    if(m_isShowList)
    {
        ui->groupBox->show();
        showList();
    }
    else
    {
        hideList();
        ui->groupBox->hide();
    }
}

void MusicPlayerr::updateVolume(int pos)
{
    m_output->setVolume(0.01 * pos);
}

void MusicPlayerr::updatePosition(qint64 pos)
{
    if(ui->progressSlider->maximum() > 0)
    {
        ui->progressSlider->blockSignals(true);
        ui->progressSlider->setValue(static_cast<int>(pos));
        ui->progressSlider->blockSignals(false);
    }

    QTime currentTime(0, 0, 0);
    currentTime = currentTime.addMSecs(static_cast<int>(pos));
    QString format = currentTime.hour() > 0 ? "hh:mm:ss" : "mm:ss";
    ui->progressLabel->setText(currentTime.toString(format) + " / " + m_totalTime);
}

void MusicPlayerr::updateDuration(qint64 dur)
{
    ui->progressSlider->setRange(0, static_cast<int>(dur));
    ui->progressSlider->setEnabled(dur > 0);

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

// 进度跳转
void MusicPlayerr::setPositionByClick(int pos)
{
    if(pos >= 0 && pos <= ui->progressSlider->maximum())
    {
        m_player->pause();
        m_player->setPosition(pos);
        m_player->play();
    }
}

// 文件选择功能
void MusicPlayerr::openFile()
{

    // 打开文件夹选择对话框
    QString folderPath = QFileDialog::getExistingDirectory(
                             nullptr,                  // 父窗口（nullptr 表示无父窗口）
                             "选择文件夹",             // 对话框标题
                             QDir::homePath(),         // 默认打开的目录（如用户主目录）
                             QFileDialog::ShowDirsOnly // 仅显示文件夹（不显示文件）
                         );
    loadDir(folderPath);

}

void MusicPlayerr::handleMediaStatus(QMediaPlayer::MediaStatus status)
{
    if(m_player->mediaStatus() == QMediaPlayer::EndOfMedia)
    {
        emit ui->nextBtn->clicked();
    }
}

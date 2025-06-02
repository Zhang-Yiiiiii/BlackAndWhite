#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QDialog>

class MusicPlayer : public QDialog
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = nullptr);

private slots:
    void updatePosition(qint64 pos);
    void updateDuration(qint64 dur);

    void togglePlayPause(); //切换暂停

    void openFile();
    void setPositionByClick(int pos);

    void toggleMute();  //切换静音
    void handleMediaStatus(QMediaPlayer::MediaStatus status);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    void updatePlayPauseIcon();
    void loadDefaultMusic();

    QMediaPlayer* m_player;
    QAudioOutput* m_output;

    // UI 组件
    QLabel* m_backgroundLabel;
    QSlider* m_slider;
    QLabel* m_timeLabel;
    QPushButton* m_playButton;
    QPushButton* m_openButton;
    QPushButton* m_loopButton;
    QSlider* m_volumeSlider;
    QLabel* m_volumeLabel;
    QPushButton* m_muteButton;

    // 状态变量
    bool m_loop = true;
    bool m_userLoaded = false;
    bool m_isSeeking = false;
    bool m_isMuted = false;
    QString m_totalTime;
};

#endif // MUSICPLAYER_H

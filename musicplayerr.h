#ifndef MUSICPLAYERR_H
#define MUSICPLAYERR_H

/*****************************************************************
 * class: MusicPlayerr （背景音乐播放器）
 *
 * 用处: 支持用户自行选择音乐
 *****************************************************************/

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QMediaPlayer>
#include <QDialog>

namespace Ui
{
    class MusicPlayerr;
}

enum PLAYMODE
{
    ORDER_MODE,
    RANDOM_MODE,
    CIRCLE_MODE
};

class MusicPlayerr : public QDialog
{
    Q_OBJECT

public:
    explicit MusicPlayerr(QWidget *parent = nullptr);
    ~MusicPlayerr();

private:
    //设置背景
    void setBackground(const QString fileName);

    //设置按钮样式
    void setBtnStyle(QPushButton* btn, const QString fileName);

    //初始化按钮
    void initBtns();

    //加载指定文件夹
    void loadDir(const QString &fileName);

    void startMusic();

    //列表滑出
    void showList();

    //列表滑入
    void hideList();

    void onPrevBtnclicked();
    void onPlayBtnclicked();
    void onModeBtnclicked();
    void onNextBtnclicked();
    void onListBtnclicked();

    void updateVolume(int pos);
    void updatePosition(qint64 pos);
    void updateDuration(qint64 dur);
    void setPositionByClick(int pos);
    void openFile();
    void handleMediaStatus(QMediaPlayer::MediaStatus status);

    QMediaPlayer* m_player;

    PLAYMODE m_mode = ORDER_MODE;

    QString m_dir;

    bool m_isShowList = false;  //默认隐藏列表

    QAudioOutput* m_output;

    QString m_totalTime;

private:
    Ui::MusicPlayerr* ui;
};

#endif // MUSICPLAYERR_H

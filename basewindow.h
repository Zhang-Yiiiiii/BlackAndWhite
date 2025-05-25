#ifndef BASEWINDOW_H
#define BASEWINDOW_H

/*****************************************************************
 * class: BaseWindow （基窗口类）
 *
 * 用处: 用于建立窗口框架、统一风格
 *****************************************************************/

#include <QMainWindow>
#include <QMenuBar>
#include <QPixmap>
#include <QPainter>
#include "musicplayer.h"
#include "GameHelpDialog.h"

namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:

    //------------------------构造析构----------------------------------

    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

    //------------------------公共方法----------------------------------

    //设置音乐播放器
    void setMusicPlayer(MusicPlayer*);

protected:

    //------------------------保护属性----------------------------------

    QPixmap m_background;
    QMenuBar* m_menubar;    //菜单栏

    QMenu* m_startMenu;   //开始菜单
    QMenu* m_gameMenu;    //游戏菜单
    QMenu* m_toolMenu;    //工具菜单

    QMenu* m_rule;              //说明菜单项

    GameHelpDialog* m_gameHelpDia;     //游戏帮助说明窗口
    // QAction* m_antRule;         //兰顿蚂蚁说明
    // QAction* m_lightOutRule;    //熄灯游戏说明
    QAction* m_quitAction;      //退出游戏菜单项
    QAction* m_musicAction;     //音乐菜单项

    MusicPlayer* m_musicPlayer;  //音乐播放器

    //------------------------保护方法----------------------------------

    virtual void paintEvent(QPaintEvent*) override;

protected slots:
    //------------------------保护槽----------------------------------

    //显示兰顿蚂蚁说明
    void onShowAntRule();

    //显示熄灯游戏说明
    void onShowLightOutRule();

private:
    Ui::BaseWindow* ui;
};

#endif // BASEWINDOW_H

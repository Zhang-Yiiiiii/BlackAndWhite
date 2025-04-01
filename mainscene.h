#ifndef MAINSCENE_H
#define MAINSCENE_H

/*
 * class: MainScene （主场景类）
 *
 * 用处： 用于显示主页面、显示选关按钮、进行登录、用户注册、创建地图、说明游戏规则
 *       进行联机
 *
 */

#include "config.h"
#include "antgame.h"
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include "hexagon.h"
#include "buildmapdialog.h"
#include "usermanager.h"
#include <QToolTip>
#include <QLayout>
#include "loginwindow.h"
#include "onlinewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainScene;
}

QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:

    //构造和析构
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

private:
    //当前用户名和密码
    QString m_userName = "";
    QString m_password = "";

    //关卡按钮数组
    Hexagon* m_selectBtns[SELECTBTNNUMBER];

    //游戏关卡界面
    AntGame* m_gameScene = nullptr;

    //自建地图的对话框
    BuildMapDialog* m_mydialog;

    //用户管理员
    UserManager* m_usermanager = nullptr;

    //联机窗口
    OnlineWindow* m_onlineWindow = nullptr;

    //登录窗口
    LoginWindow* m_loginWindow = nullptr;

    //是否是联机模式
    bool m_isOnlineMode = false;

    //记录双方时间
    int m_ourTotalTime = 0;
    int m_rivalTotalTime = 0;

    //双方是否已经完成游戏
    bool m_isWeFinished = false;
    bool m_isRivalFinished = false;

    //比较双方结果
    void compareResults(int ourTime, int rivalTime);

    //重写绘图事件
    void paintEvent(QPaintEvent* e);

    //显示选关六边形
    void showSelectBtn();

    //自建地图函数
    void selfBuildGame(gameMode buildWay);

    //显示自建地图对话框
    void showBuildDialog(gameMode buildWay);

    //进入游戏场景
    void enterGameScene
    (int gameLevel, gameMode enterWay = playMode, int gameStep = 1, int bugX = 1, int bugY = 1,
     int bugDirection = 1);

    //创建保存按钮
    void createSaveButton(int gameStep, int bugX, int bugY, int bugDirection, gameMode buildWay);

    //处理保存按钮点击
    void handleSaveButtonClicked(gameMode buildWay, int gameStep, int bugX, int bugY, int bugDirection);

    //显示登录对话框
    void showLoginWindow();

signals:

private:
    Ui::MainScene* ui;

private slots:
    //用户登录
    void onUserLogin();

    //进入游戏场景
    void onHexagonClicked(int gameLevel);

    //处理建图对话框返回的信息
    void onMapingInfoReceived(gameMode buildWay);

    //处理返回信号
    void onGameSceneChangeBack();

    //处理登录信息
    void onUserConfirmLogin();

    //用户确定注册
    void onUserConfirmRegister();

};

#endif // MAINSCENE_H

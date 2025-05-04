#ifndef MAINSCENE_H
#define MAINSCENE_H

/*
 * class: MainScene （主场景类）
 *
 * 用处： 用于显示主页面、显示选关按钮、进行登录、用户注册、创建地图、说明游戏规则
 *       进行联机
 *
 */
#include <QToolTip>
#include <QLayout>
#include <QInputDialog>
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QPauseAnimation>

#include "basewindow.h"
#include "config.h"
#include "hexagon.h"
#include "buildmapdialog.h"
#include "usermanager.h"
#include "loginwindow.h"
#include "onlinewindow.h"
#include "abstractgamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainScene;
}

QT_END_NAMESPACE

class MainScene : public BaseWindow
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
    AbstractGameScene* m_gameScene = nullptr;

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

    //初始化选关按钮
    void initSelectBtn();

    //显示选关六边形
    void showSelectBtn();

    //自建ant地图函数
    void buildAntGame(gameMode buildWay);

    //自建light地图函数
    void buildLightGame();

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

    //设置联机模式
    void setOnlineMode();

    //设置动画
    void setAnimations();
    void setAnimation(QWidget* widget, QSequentialAnimationGroup* animaltionGroup);

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

    //用户点击联机按钮
    void onOnlineTriggerd();

    //用户点击断开联机
    void onDisconnectTriggerd();

};

#endif // MAINSCENE_H

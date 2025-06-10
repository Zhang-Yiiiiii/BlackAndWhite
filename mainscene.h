#ifndef MAINSCENE_H
#define MAINSCENE_H

/*****************************************************************
 * class: MainScene （主场景类）
 *
 * 用处： 用于显示主页面、显示选关按钮、进行登录、用户注册、创建地图、进行联机、音乐播放
 *
 * 功能模块排列：
 *          1.自身功能
 *          2.登录
 *          3.建图
 *          4.联机
 *          5.音乐
 *
 ********************************************************************/

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
#include "avatarwidget.h"
#include "gamehelpdialog.h"

class MainScene : public BaseWindow
{
    Q_OBJECT

public:

    //------------------------构造和析构----------------------------------

    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    // bool eventFilter(QObject *watched, QEvent *event ) override;

    void showEvent(QShowEvent *event) override;

private:

    //------------------------私有属性----------------------------------

    //用户
    User* m_user = nullptr;

    //当前用户名和密码
    QString m_userName = "default";
    QString m_password = "default";

    //头像
    AvatarWidget* m_avatarWidget;
    User* m_currentUser;

    //关卡按钮数组
    Hexagon* m_selectBtns[SELECTBTNNUMBER];

    //用户管理员
    UserManager* m_usermanager = nullptr;

    //游戏关卡界面
    AbstractGameScene* m_gameScene = nullptr;

    //登录窗口
    LoginWindow* m_loginWindow = nullptr;

    //自建地图的对话框
    BuildMapDialog* m_mappingDialog = nullptr;

    //联机窗口
    OnlineWindow* m_onlineWindow = nullptr;

    QAction* disconnectAction = nullptr;

    //是否是联机模式
    bool m_isOnlineMode = false;

    //是否正在游戏
    bool m_isGaming = false;

    //记录双方时间
    int m_ourTotalTime = 0;
    int m_rivalTotalTime = 0;

    //双方是否已经完成游戏
    bool m_isWeFinished = false;
    bool m_isRivalFinished = false;

    //------------------------私有方法----------------------------------

    //显示游戏名称
    void showGameTitle();

    //初始化选关按钮
    void initSelectBtn();

    //显示选关六边形
    void showSelectBtn();

    //设置动画
    void setAnimations();

    //进入游戏场景
    void enterGameScene(int gameLevel, BuildWay enterWay = playMode, int gameStep = 1, int bugX = 1, int bugY = 1, int bugDirection = 0);

    //显示登录对话框
    void showLoginWindow();

    //自建ant地图函数
    void buildAntGame(BuildWay buildWay);

    //自建light地图函数
    void buildLightGame();

    //显示自建地图对话框
    void showBuildDialog(BuildWay buildWay);

    //创建保存按钮
    void createSaveButton(int gameStep, int bugX, int bugY, int bugDirection, BuildWay buildWay);

    //创建模拟按钮
    void createSimulationButton(int gameStep, int bugX, int bugY, int bugDirection, BuildWay buildWay);

    //设置联机模式
    void setOnlineMode();

    //比较联机双方结果
    void compareResults(int ourTime, int rivalTime);

    //显示头像
    void showAvatar();

private slots:
    //------------------------私有槽----------------------------------

    //选关按钮被点击
    void onHexagonClicked(int gameLevel);

    //处理返回信号
    void onGameSceneChangeBack();

    //点击登录按钮
    void onLoginClicked();

    //处理登录信息
    void onUserConfirmLogin();

    //用户确定注册
    void onUserConfirmRegister();

    //处理建图对话框返回的信息
    void onMapingInfoReceived(BuildWay buildWay);

    //保存按钮点击
    void onSaveButtonClicked(BuildWay buildWay, int gameStep, int bugX, int bugY, int bugDirection);

    //模拟按钮的点击
    void onSimuButtonClicked(BuildWay buildWay, int gameStep, int bugX, int bugY, int bugDirection, bool &flag);

    //用户点击联机按钮
    void onOnlineTriggerd();

    //用户点击断开联机
    void onDisconnectTriggerd();

signals:
    void sceneShow();

};

#endif // MAINSCENE_H

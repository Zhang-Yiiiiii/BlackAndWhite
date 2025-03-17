#ifndef MAINSCENE_H
#define MAINSCENE_H

/*
 * class: MainScene （主场景类）
 *
 * 用处： 用于显示主页面、显示选关按钮、进行登录、用户注册、创建地图、说明游戏规则
 *
 */

#include "config.h"
#include "gamescene.h"
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include "hexagon.h"
#include "mydialog.h"
#include "usermanager.h"
#include <QToolTip>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
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
    Hexagon *m_selectBtns[SELECTBTNNUMBER];

    //游戏关卡界面
    GameScene * m_gameScene = nullptr;

    //自建地图的对话框
    myDialog * m_mydialog;

    //游戏管理员
    UserManager * m_usermanager = nullptr;

    //用户注册
    void userRegister();

    //重写绘图事件
    void paintEvent(QPaintEvent* e);

    //显示选关六边形
    void showSelectBtn();

    //自建地图函数  buildWay==0:起点建图 buildWay==1:终点建图
    void selfBuildGame(bool buildWay);

    //显示自建地图对话框
    void showBuildDialog(bool buildWay);

    //进入游戏场景  enterWay-> 0:起点建图  1：终点建图   2：游戏模式
    void enterGameScene(int gameLevel, int gameStep = 1, int bugX = 1, int bugY = 1, int bugDirection = 1, int enterWay = 3);

    //创建保存按钮
    void createSaveButton(int gameStep, int bugX,int bugY,int bugDirection, bool buildWay);

    //处理保存按钮点击
    void handleSaveButtonClicked(bool buildWay, int gameStep, int bugX,int bugY,int bugDirection);

private:
    Ui::MainScene *ui;

private slots:
    //用户登录
    void onUserLogin();

    //进入游戏场景
    void onHexagonClicked(int gameLevel);

    //处理对话框返回的信息
    void onDialogInfoReceived(bool buildWay);

    //处理返回信号
    void onGameSceneChangeBack();


};
#endif // MAINSCENE_H

#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "config.h"
#include "data.h"
#include "gamescene.h"
#include <QMainWindow>
#include <QMenu>
#include <QPainter>
#include "hexagon.h"
#include "mydialog.h"
#include "usermanager.h"
#include "loginwindow.h"
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
    MainScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent* e);

    //关卡按钮数组
    Hexagon *selectBtns[SELECTBTNNUMBER];

    //显示选关六边形
    void showSelectBtn();

    //游戏关卡界面
    GameScene * gameScene = nullptr;

    //自建地图函数  buildWay==0:起点建图 buildWay==1:终点建图
    void selfBuildGame(bool buildWay);

    //自建地图的对话框
    myDialog * mydialog;

    //游戏管理员
    UserManager * usermanager = nullptr;

    //当前用户名和密码
    QString m_userName = "";
    QString m_password = "";

    //用户登录
    void userLogin();

    //用户注册
    void userRegister();


    ~MainScene();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H

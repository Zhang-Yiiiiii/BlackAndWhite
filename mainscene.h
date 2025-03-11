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

    //显示选关六边形
    Hexagon *selectBtns[SELECTBTNNUMBER];
    void showSelectBtn();

    //游戏关卡界面
    GameScene * gameScene = nullptr;

    //自建地图的对话框
    myDialog * mydialog;


    ~MainScene();

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H

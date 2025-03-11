#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "config.h"
#include "data.h"
#include <QApplication>
#include <QString>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include "hexagon.h"
#include "gridbutton.h"
#include <iostream>


class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScene(int gameLevel ,QWidget *parent = nullptr);


    //黑白格子
    GridButton * board[20][20];

    //显示棋盘
    void showBoard();

    //重写绘图事件
    void paintEvent(QPaintEvent * e) override;

    //游戏关数
    int gameLevel;

    //虫子图片 位置 方向
    QPixmap bugPix;
    QPoint bugPos;
    int bugDir;

    //游戏数组
    bool gameArray[20][20];

    //答案数组
    bool ansArray[20][20];

    //游戏步数
    int gameStep;

    //检验是否胜利
    bool isWin();

    //判断是否有解
    bool startIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step);  //已知起点
    bool endIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step);  //已知终点

    //保存地图的函数，用于自建地图
    void saveGame(int level,int step,int x,int y,int direction);

    //信息对象
    Data * data ;

    //析构函数
    ~GameScene();

signals:

    //返回信号
    void changeBack();
};


#endif // GAMESCENE_H

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
#include <sstream>
#include "usermanager.h"
#include "ranklist.h"
#include <QLayout>
#include <QElapsedTimer>
#include <QTimer>



class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScene(int gameLevel ,QString userName, UserManager * usermanager,QWidget *parent = nullptr);

    //设置返回按钮
    QPushButton * backBtn = nullptr;

    //重置按钮
    QPushButton * resetBtn = nullptr;

    //设置提交按钮
    QPushButton * submitBtn = nullptr;

    //用户名
    QString userName;

    //显示游戏说明
    void showRule();

    //显示排行榜
    void showRankList();

    //更新排行榜
    void updateRankList();

    //黑白格子
    GridButton * board[20][20];

    //显示棋盘
    void showBoard();

    //显示虫子
    void showBug();

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

    //重置棋盘
    void resetGame();

    //判断是否有解
    bool startIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step);  //已知起点
    bool endIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step);  //已知终点

    //保存地图的函数，用于自建地图  buildWay==0:起点建图  buildWay==1：终点建图
    void saveGame(bool buildWay,int step,int x,int y,int direction);

    //信息对象
    Data * data ;

    //用户管理员
    UserManager * usermanager;

    //时间label
    QLabel * timeLabel;

    //罚时label
    QLabel * timePenaltyLabel;

    //罚时的秒数
    int penaltyTime = 0;

    //定时器
    QElapsedTimer * timer;

    //控制显示时间
    QTimer * showTimer;

    //保存用户通关之后的时间
    void saveTotalTime();




    //析构函数
    ~GameScene();

signals:

    //返回信号
    void changeBack();

public slots:

    //更新时间
    void updateTime();

};


#endif // GAMESCENE_H

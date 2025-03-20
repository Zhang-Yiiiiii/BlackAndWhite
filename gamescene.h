#ifndef GAMESCENE_H
#define GAMESCENE_H

/*
 * class: GameScene （游戏界面）
 *
 * 用处: 用于展示游戏、记录通关时间、展示排行榜、对用户进行游戏上的交互
 */

#include "data.h"
#include <QApplication>
#include <QString>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include "gridbutton.h"
#include "usermanager.h"
#include <QLayout>
#include <QElapsedTimer>
#include <QTimer>

class GameScene : public QMainWindow
{
    Q_OBJECT
public:
    //构造和析构
    explicit GameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr);
    ~GameScene();

    //设置提交按钮
    QPushButton* submitBtn = nullptr;

    //显示游戏说明
    void showRule();

    //保存地图的函数，用于自建地图  buildWay==0:起点建图  buildWay==1：终点建图
    void saveGame(bool buildWay, int step, int x, int y, int direction);

private:
    //设置返回按钮
    QPushButton* backBtn = nullptr;

    //重置按钮
    QPushButton* resetBtn = nullptr;

    //用户名
    QString m_userName;

    //游戏关数
    const int m_gameLevel;

    //游戏步数
    int m_gameStep;

    //虫子图片 位置 方向
    QPixmap m_bugPix;
    QPoint m_bugPos;
    int m_bugDir;

    //信息对象
    Data* m_data ;

    //用户管理员
    UserManager* m_usermanager;

    //时间label
    QLabel* m_timeLabel;

    //罚时label
    QLabel* m_timePenaltyLabel;

    //定时器
    QElapsedTimer* m_elapsedTimer;

    //控制显示时间
    QTimer* m_showTimer;

    //更新排行榜
    void updateRankList();

    //黑白格子
    GridButton* m_board[20][20];

    //显示棋盘
    void showBoard();

    //显示虫子
    void showBug();

    //重写绘图事件
    void paintEvent(QPaintEvent * e) override;

    //游戏数组
    bool m_gameArray[20][20];

    //答案数组
    bool m_ansArray[20][20];

    //检验是否胜利
    bool isWin();

    //重置棋盘
    void resetGame();

    //判断是否有解
    bool startingPointMaping(bool gameArray[][20], QPoint pos, int bugDir, int step); //已知起点
    bool destinationMaping(bool gameArray[][20], QPoint pos, int bugDir, int step); //已知终点

    //罚时的秒数
    int m_penaltyTime = 0;

    //保存用户通关之后的时间
    void saveTotalTime();

    //显示步数label
    void showStepLabel();

    //显示时间label
    void showTimeLabel();

    //初始化定时器
    void initTimer();

    //初始化游戏信息
    void initGameInfo();

    //显示提交、返回、重置按钮
    void showPushButton();

signals:

    //返回信号
    void changeBack();

public slots:

    //更新时间
    void updateTime();

    //显示排行榜
    void showRankList();

};

#endif // GAMESCENE_H

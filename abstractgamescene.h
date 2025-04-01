#ifndef ABSTRACTGAMESCENE_H
#define ABSTRACTGAMESCENE_H

#include <QMainWindow>
#include "data.h"
#include <QApplication>
#include <QString>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include "gridbutton.h"
#include "usermanager.h"
#include <QLayout>
#include <QElapsedTimer>
#include <QTimer>
#include "ranklist.h"
#include <vector>

enum gameMode
{
    playMode,   //游戏模式
    startingPointMode,  //起点建图
    destinationMode,    //终点建图
    onlineMode,     //联机模式
};

class AbstractGameScene : public QMainWindow
{
    Q_OBJECT
public:
    //构造和析构
    explicit AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr);
    ~AbstractGameScene();

    //设置提交按钮
    QPushButton* submitBtn = nullptr;

    //游戏模式
    gameMode m_gameMode = playMode;

    //显示游戏说明
    void showRule();

    //保存地图的函数，用于自建地图
    virtual void saveGame() = 0;

    //获取用户当前总时间
    virtual int getTotalTime() = 0;

protected:
    //设置返回按钮
    QPushButton* backBtn = nullptr;

    //重置按钮
    QPushButton* resetBtn = nullptr;

    //用户名
    QString m_userName;

    //游戏关数
    const int m_gameLevel;

    //信息对象
    Data* m_data ;

    //用户管理员
    UserManager* m_usermanager;

    //时间label
    QLabel* m_timeLabel;

    //经过时间的秒数
    int m_passingTime = 0;

    //定时器
    QElapsedTimer* m_elapsedTimer;

    //控制显示时间定时器
    QTimer* m_showTimer;

    //排行榜窗口
    RankList* m_rankWindow = nullptr;

    //棋盘的行数和列数
    int m_boardRow;
    int m_boardCol;

    //黑白格子
    std::vector<std::vector<GridButton*>> m_board;

    //得到棋盘尺寸
    void setboardSize();

    //显示棋盘
    void showBoard();

    //重写绘图事件
    void paintEvent(QPaintEvent * e) override;

    //游戏数组
    std::vector<std::vector<bool>> m_gameArray;

    //检验是否胜利
    virtual bool isWin() = 0;

    //重置棋盘
    void resetGame();

    //保存用户通关之后的时间
    int saveTotalTime();

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
    void gameOver(int totalTime);

public slots:

    //更新显示时间
    void updateTime();

    //显示排行榜
    void showRankList();

};

#endif // ABSTRACTGAMESCENE_H

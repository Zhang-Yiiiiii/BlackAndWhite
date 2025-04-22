#ifndef ABSTRACTGAMESCENE_H
#define ABSTRACTGAMESCENE_H

#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPainter>
#include <QLayout>
#include <QElapsedTimer>
#include <QTimer>
#include <vector>

#include "ranklist.h"
#include "gridbutton.h"
#include "usermanager.h"
#include "data.h"

enum gameMode
{
    playMode,   //游戏模式
    lightBuildMode,     //熄灯建图
    startingPointMode,  //起点建图
    destinationMode,    //终点建图
    onlineMode,     //联机模式
};

class AbstractGameScene : public QMainWindow
{
    Q_OBJECT
public:
    //构造和析构
    explicit AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, gameMode mode = playMode);
    ~AbstractGameScene();

    //设置提交按钮
    QPushButton* submitBtn = nullptr;

    //游戏模式
    gameMode m_gameMode = playMode;

    //显示游戏说明
    void showRule();

    //保存地图的函数，用于自建地图
    virtual void saveGame() = 0;

protected:

    //设置返回按钮
    QPushButton* backBtn = nullptr;

    //重置按钮
    QPushButton* resetBtn = nullptr;

    //游戏关数
    const int m_gameLevel;

    //用户名
    QString m_userName = "";

    //游戏信息对象
    Data* m_data = nullptr;

    //用户管理员
    UserManager* m_usermanager = nullptr;

    //时间label
    QLabel* m_timeLabel = nullptr;

    //经过时间的秒数
    int m_passingTime = 0;

    //定时器
    QElapsedTimer* m_elapsedTimer = nullptr;

    //控制显示时间定时器
    QTimer* m_showTimer = nullptr;

    //排行榜窗口
    RankList* m_rankWindow = nullptr;

    //棋盘的行数和列数
    int m_boardRow;
    int m_boardCol;

    //黑白格子
    std::vector<std::vector<GridButton*>> m_board;

    //游戏数组
    std::vector<std::vector<bool>> m_gameArray;

    //答案数组
    std::vector<std::vector<bool>> m_ansArray;

    //重写绘图事件
    void paintEvent(QPaintEvent * e) override;

    //得到棋盘尺寸
    void setboardSize();

    //初始化vector大小
    void initVector();

    //重置棋盘
    void resetGame();

    //初始化定时器
    void initTimer();

    //保存用户通关之后的时间
    int saveTotalTime();

    //获取用户当前总时间
    virtual int getTotalTime() = 0;

    //检验是否胜利
    virtual bool isWin() = 0;

    //显示棋盘
    virtual void showBoard();

    //显示时间label
    virtual void showTimeLabel();

    //初始化游戏信息
    virtual void initGameInfo();

    //设置提交、返回、重置按钮
    virtual void setSubmitBtn();
    virtual void setBackBtn();
    virtual void setResetBtn();

    //显示提交、返回、重置按钮
    void showPushButton();

signals:

    //返回信号
    void changeBack();
    void gameOver(int totalTime);

public slots:

    //更新显示时间
    virtual void updateTime();

    //显示排行榜
    void showRankList();

    virtual void onSubmitBtnClicked();

    virtual void onResetBtnClicked();
};

#endif // ABSTRACTGAMESCENE_H

#ifndef ABSTRACTGAMESCENE_H
#define ABSTRACTGAMESCENE_H

/*
 * class: AbstractGameScene （抽象游戏类）
 *
 * 用处: 用于展示游戏、记录通关时间、展示排行榜、对用户进行游戏上的交互
 */

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
#include <QCloseEvent>

#include "basewindow.h"
#include "ranklist.h"
#include "gridbutton.h"
#include "usermanager.h"
#include "data.h"
#include "animator.h"

enum gameMode
{
    playMode,   //游戏模式
    lightBuildMode,     //熄灯建图
    startingPointMode,  //起点建图
    destinationMode,    //终点建图
    onlineMode,     //联机模式
};

class AbstractGameScene : public BaseWindow
{
    Q_OBJECT
public:
    //构造和析构
    explicit AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, gameMode mode = playMode);
    virtual ~AbstractGameScene();

    //设置提交按钮
    QPushButton* submitBtn = nullptr;

    //随机按钮
    QPushButton* randomBtn = nullptr;

    //游戏模式
    gameMode m_gameMode = playMode;

    //关闭窗口的标志
    bool m_isInternalclose = true;  //如果是点击窗口的关闭按钮则关闭程序

    //保存地图的函数，用于自建地图
    virtual void saveGame() {};

    //设置动画类型
    void setAnimationType(Animator::AnimationType);

    //重写关闭事件
    void closeEvent(QCloseEvent* event) override;

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
    QElapsedTimer m_elapsedTimer;

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

    //提示数组
    std::vector<std::vector<bool>> m_tipsArray;

    //提示按钮数组
    std::vector<QPushButton*> m_tipsButtons;

    //动画效果  默认是淡入
    Animator::AnimationType m_animationType = Animator::FadeIn;

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
    virtual int getTotalTime() const = 0;

    //检验是否胜利
    virtual bool isWin() const = 0;

    //显示棋盘
    virtual void showBoard(bool isVisible = true);

    //显示时间label
    virtual void showTimeLabel();

    //初始化游戏信息
    virtual void initGameInfo();

    //设置提交、返回、重置按钮
    virtual void setSubmitBtn();
    virtual void setBackBtn();
    virtual void setResetBtn();

    //设置随机生成地图按钮
    void setRandomBtn();

    //显示提交、返回、重置按钮
    void showPushButton();

    //设置动画效果
    void setAnimation(int delay = 4);

    //清空提示按钮
    void clearTipsButton();

    //生成提示数组
    virtual void generateTipArray() = 0;

    //设置label样式
    void setLabelStyle(QLabel* label);

signals:

    //返回信号
    void changeBack();
    void gameOver(int totalTime);

public slots:

    //更新显示时间
    virtual void updateTime();

    //显示排行榜
    void showRankList();

    //提交按钮被点击
    virtual void onSubmitBtnClicked();

    //重置按钮被点击
    virtual void onResetBtnClicked();

    //随机生成地图按钮被点击
    void onRandomBtnClicked();

    //棋盘被点击
    virtual void onBoardClicked(int x, int y);

    //显示提示功能
    void onShowTips();

};

#endif // ABSTRACTGAMESCENE_H

#ifndef ABSTRACTGAMESCENE_H
#define ABSTRACTGAMESCENE_H

/*****************************************************************
 * class: AbstractGameScene （抽象游戏类）
 *
 * 用处: 用于展示游戏、记录通关时间、展示排行榜、对用户进行游戏上的交互
 *****************************************************************/

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
#include <QMap>

#include "basewindow.h"
#include "ranklist.h"
#include "gridbutton.h"
#include "usermanager.h"
#include "data.h"
#include "animator.h"

//------------------------公有类型----------------------------------
enum BuildWay
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

    //------------------------构造和析构----------------------------------
    explicit AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, BuildWay mode = playMode);
    virtual ~AbstractGameScene();

    //------------------------公有方法----------------------------------

    //隐藏提交按钮
    AbstractGameScene* hideSubmitBtn();

    //显示随机按钮
    AbstractGameScene* showRandomBtn();

    //是否为内部关闭
    AbstractGameScene* setInternalClose(bool flag);

    //设置动画类型
    void setAnimationType(Animator::AnimationType);

    //保存可解信息
    void saveSolvableInfo(const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans);
    void saveSolvableInfo(const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans, int steps, int dir, QPoint pos);

    //评分
    virtual ScoreLevel Scoring() = 0;

    //禁用按钮
    virtual void setBtnEnabled(bool enable);

protected:
    //------------------------保护属性----------------------------------

    //用户名
    QString m_userName = "default";

    //游戏关数
    int m_gameLevel;

    //棋盘的行数和列数
    int m_boardRow;
    int m_boardCol;

    //棋盘位置
    QPoint boardPos;

    //棋盘
    std::vector<std::vector<GridButton*>> m_board;

    //游戏数组
    std::vector<std::vector<bool>> m_gameArray;

    //答案数组
    std::vector<std::vector<bool>> m_ansArray;

    //提示数组
    std::vector<std::vector<bool>> m_tipsArray;

    //提示按钮数组
    std::vector<QPushButton*> m_tipsButtons;

    //游戏信息对象
    Data* m_data = nullptr;

    //用户管理员
    UserManager* m_usermanager = nullptr;

    //重置按钮
    QPushButton* resetBtn = nullptr;

    //提交按钮
    QPushButton* submitBtn = nullptr;

    //随机按钮
    QPushButton* randomBtn = nullptr;

    //返回按钮
    QPushButton* backBtn = nullptr;

    //提示按钮
    QAction* showAnswearAction = nullptr;

    //游戏模式
    BuildWay m_gameMode = playMode;

    //经过时间的秒数
    int m_passingTime = 0;

    //罚时的秒数
    int m_penaltyTime = 0;

    //时间label
    QLabel* m_timeLabel = nullptr;

    //罚时
    QLabel* m_timePenaltyLabel = nullptr;

    //难度等级
    QLabel * m_difficultyLabel = nullptr;

    //计时器
    QElapsedTimer m_elapsedTimer;

    //控制显示时间定时器
    QTimer* m_showTimer = nullptr;

    //排行榜窗口
    RankList* m_rankWindow = nullptr;

    //动画效果  默认是淡入
    Animator::AnimationType m_animationType = Animator::FadeIn;

    //关闭窗口的标志
    bool m_isInternalclose = true;  //如果是点击窗口的关闭按钮则关闭程序

    //------------------------保护方法----------------------------------

    //设置棋盘尺寸
    void setboardSize();

    //初始化vector大小
    void initVector();

    //初始化游戏信息
    void initGameInfo();

    //显示棋盘
    void showBoard(bool isVisible = true);

    //显示时间label
    void showTimeLabel();

    //显示难度等级label
    void showDifficultyLabel(QString difficulty);

    //初始化定时器
    void initTimer();

    //保存用户通关之后的时间
    int saveTotalTime();

    //获取用户当前总时间
    virtual int getTotalTime() const;

    //检验是否胜利
    virtual bool isWin() const = 0;

    //设置提交、返回、重置按钮
    void setSubmitBtn();
    void setBackBtn();
    void setResetBtn();
    void setRandomBtn();    //设置随机生成地图按钮

    //重置棋盘
    void resetGame();

    //显示提交、返回、重置按钮
    void showPushButton();

    //设置动画效果
    void setAnimation(int delay = 6);

    //生成提示数组
    virtual void generateTipArray() = 0;

    //清空提示按钮
    void clearTipsButton();

    //设置label样式
    void setLabelStyle(QLabel* label);

    //重写绘图事件
    //void paintEvent(QPaintEvent * event) override;

    //重写showEvent
    void showEvent(QShowEvent* event) override;

    //重写关闭事件
    void closeEvent(QCloseEvent* event) override;

    //判定难度
    virtual QString judgeDiff() = 0;

    //计算经验
    virtual unsigned calculateExp() = 0;

signals:
    //------------------------信号----------------------------------

    //返回信号
    void changeBack();

    //游戏完成信号
    void gameOver(int totalTime);

    //显示信号
    void sceneShow();

    //重置棋盘发出的信号
    void resetGameSignal();

public slots:
    //------------------------公共槽----------------------------------

    //棋盘被点击
    virtual void onBoardClicked(int x, int y);

    //提交按钮被点击
    virtual void onSubmitBtnClicked();

    //重置按钮被点击
    virtual void onResetBtnClicked();

    //随机生成地图按钮被点击
    virtual void onRandomBtnClicked();

    //更新显示时间
    virtual void onUpdateTime();

    //显示提示功能
    void onShowTips();

    //显示排行榜
    void onRankActionClicked();

};

#endif // ABSTRACTGAMESCENE_H

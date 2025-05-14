#ifndef ANTGAME_H
#define ANTGAME_H

/*****************************************************************
 * class: AntGame （兰顿蚂蚁）
 *
 * 用处: 处理游戏时间记录、判断是否有解
 *****************************************************************/

#include <QMainWindow>
#include "abstractgamescene.h"

class AntGame : public AbstractGameScene
{
    Q_OBJECT
public:
    //------------------------构造析构----------------------------------

    explicit AntGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, BuildWay mode = playMode);
    ~AntGame();

    //------------------------公有方法----------------------------------

    //保存游戏数据
    void saveGame(BuildWay buildWay, int step, int x, int y, int direction);

private:

    //------------------------私有属性----------------------------------
    //游戏步数
    int m_gameStep = 0;

    //虫子图片 位置 方向
    QPixmap m_bugPix;
    QPoint m_bugPos;
    int m_bugDir;

    QLabel* m_timePenaltyLabel = nullptr;     //罚时label

    QLabel* m_currentStepsLabel = nullptr;    //当前步数label

    int m_currentSteps = 0;         //当前步数

    int m_penaltyTime = 0;          //罚时的秒数

    //------------------------私有方法----------------------------------

    void initGameInfo() override;   //初始化游戏信息

    void initBugInfo();             //初始化虫子信息

    void showBug();                 //显示虫子

    void showTimeLabel() override;  //显示时间label

    int getTotalTime() const override;    //获取总时间

    void showStepLabel();           //显示步数label

    void updateCurrentSteps(unsigned int steps); //更新当前步数

    bool isWin() const override;          //检验是否胜利

    //判断是否有解
    bool startingPointMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知起点
    bool destinationMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知终点

    void generateTipArray() override;   //生成提示数组

public slots:

    //------------------------私有槽----------------------------------

    void onSubmitBtnClicked() override; //提交按钮被点击

    void onResetBtnClicked() override;  //重置按钮被点击

    void onBoardClicked(int x, int y) override; //棋盘被点击

    void onShowCurrentSteps();    //显示当前步数

    void onUpdateTime() override; //更新时间

};

#endif // ANTGAME_H

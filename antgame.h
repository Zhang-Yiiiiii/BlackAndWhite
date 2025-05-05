#ifndef ANTGAME_H
#define ANTGAME_H

#include <QMainWindow>
#include "abstractgamescene.h"

class AntGame : public AbstractGameScene
{
    Q_OBJECT
public:
    explicit AntGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, gameMode mode = playMode);
    ~AntGame();

    //保存地图的函数，用于自建地图
    void saveGame() override {};

    void saveGame(gameMode buildWay, int step, int x, int y, int direction);

private:

    //游戏步数
    int m_gameStep;

    //虫子图片 位置 方向
    QPixmap m_bugPix;
    QPoint m_bugPos;
    int m_bugDir;

    QLabel* m_timePenaltyLabel;     //罚时label

    QLabel* m_currentStepsLabel = nullptr;    //当前步数label

    int m_currentSteps = 0;         //当前步数

    int m_penaltyTime = 0;          //罚时的秒数

    void updateCurrentSteps(unsigned int steps); //更新当前步数

    void initGameInfo() override;   //初始化游戏信息

    void showTimeLabel() override;  //显示时间label

    int getTotalTime() const override;    //获取总时间

    void initBugInfo();             //初始化虫子信息

    void showBug();                 //显示虫子

    void showStepLabel();           //显示步数label

    bool isWin() const override;          //检验是否胜利

    //判断是否有解
    bool startingPointMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知起点
    bool destinationMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知终点

    void generateTipArray() override;   //生成提示数组

public slots:

    void updateTime() override; //更新时间

    void onSubmitBtnClicked() override; //提交按钮被点击

    void onResetBtnClicked() override;  //重置按钮被点击

    void onBoardClicked(int x, int y) override; //棋盘被点击

    void onShowCurrentSteps();    //显示当前步数

signals:

};

#endif // ANTGAME_H

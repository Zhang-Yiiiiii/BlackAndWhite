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

    void initGameInfo() override;

    void showTimeLabel() override;

    void setSubmitBtn() override;

    void setResetBtn() override;

private:
    //判断是否有解
    bool startingPointMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知起点
    bool destinationMaping(std::vector<std::vector<bool>>& gameArray, QPoint pos, int bugDir, int step); //已知终点

    //获取用户当前总时间
    int getTotalTime() override;

    //游戏步数
    int m_gameStep;

    //虫子图片 位置 方向
    QPixmap m_bugPix;
    QPoint m_bugPos;
    int m_bugDir;

    //罚时label
    QLabel* m_timePenaltyLabel;

    //罚时的秒数
    int m_penaltyTime = 0;

    //初始化虫子信息
    void initBugInfo();

    //显示虫子
    void showBug();

    //显示步数label
    void showStepLabel();

    //检验是否胜利
    bool isWin() override;

public slots:
    void updateTime() override;

signals:

};

#endif // ANTGAME_H

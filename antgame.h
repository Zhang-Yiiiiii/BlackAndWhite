#ifndef ANTGAME_H
#define ANTGAME_H

#include <QMainWindow>
#include "abstractgamescene.h"

class AntGame : public AbstractGameScene
{
    Q_OBJECT
public:
    explicit AntGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr);

    //保存地图的函数，用于自建地图
    void saveGame() override {};

    void saveGame(gameMode buildWay, int step, int x, int y, int direction);

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

    //显示虫子
    void showBug();

    //答案数组
    std::vector<std::vector<bool>> m_ansArray;

    //检验是否胜利
    bool isWin() override;

signals:

};

#endif // ANTGAME_H

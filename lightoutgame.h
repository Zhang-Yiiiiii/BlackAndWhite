#ifndef LIGHTOUTGAME_H
#define LIGHTOUTGAME_H

#include <QMainWindow>
#include "abstractgamescene.h"

class LightOutGame : public AbstractGameScene
{
    Q_OBJECT
public:
    explicit LightOutGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, gameMode mode = playMode);

    //保存地图的函数，用于自建地图
    void saveGame() override;

private:

    //初始化游戏信息
    void initGameInfo() override;

    //获取用户当前总时间
    int getTotalTime() override;

    //检验是否胜利
    bool isWin() override;

    //翻转周围格子
    void flipCells(const int x, const int y);

    //是否可解
    bool isSolvable();

    //保存可解的数据
    void saveSolvableInfo(std::vector<std::vector<bool> >& gameArray, std::vector<std::vector<bool >> & ans);

public slots:

    //重写棋盘被点击的槽函数
    void onBoardClicked(int x, int y) override;

signals:
};

#endif // LIGHTOUTGAME_H

#ifndef LIGHTOUTGAME_H
#define LIGHTOUTGAME_H

#include <QMainWindow>
#include "abstractgamescene.h"

class LightOutGame : public AbstractGameScene
{
    Q_OBJECT
public:
    explicit LightOutGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, gameMode mode = playMode);
    ~LightOutGame() {};

    //保存地图的函数，用于自建地图
    void saveGame() override;

private:
    //点击记录数组
    std::vector<std::vector<bool>> m_clickRecord;

    //获取用户当前总时间
    int getTotalTime() const override;

    //检验是否胜利
    bool isWin() const override;

    //翻转周围格子
    void flipCells(const int x, const int y);

    //是否可解
    bool isSolvable();

    //保存可解的数据
    void saveSolvableInfo(const std::vector<std::vector<bool> > &, const std::vector<std::vector<bool >> & );

    //初始化点击数组
    void initClickRecord();

    //生成提示数组
    void generateTipArray() override;

public slots:

    //重写棋盘被点击的槽函数
    void onBoardClicked(int x, int y) override;

signals:
};

#endif // LIGHTOUTGAME_H

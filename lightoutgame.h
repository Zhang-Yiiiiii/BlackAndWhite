#ifndef LIGHTOUTGAME_H
#define LIGHTOUTGAME_H

/*****************************************************************
 * class: LightOutGame (熄灯游戏)
 *
 * 用处: 处理格子翻转、判断是否有解
 *
 *****************************************************************/

#include <QMainWindow>
#include <bitset>
#include "abstractgamescene.h"

using row = std::bitset<500>;

class LightOutGame : public AbstractGameScene
{
    Q_OBJECT
public:

    //------------------------构造析构----------------------------------

    explicit LightOutGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent = nullptr, BuildWay mode = playMode);
    ~LightOutGame() {};

    //------------------------公有方法----------------------------------

    //保存地图的函数，用于自建地图
    void saveGame() ;

    //评分
    ScoreLevel Scoring() override;

private:

    //------------------------私有属性----------------------------------

    //点击记录数组
    std::vector<std::vector<bool>> m_clickRecord;

    //------------------------私有方法----------------------------------

    //初始化点击数组
    void initClickRecord();

    //翻转周围格子
    void flipCells(const int x, const int y, bool isShowAnimation = true);

    //是否可解
    bool isSolvable();

    //线性方程组求解
    bool linearAlgebra_solve(const std::vector<std::vector<bool >>& gameArray, std::vector<int>& x);

    //部分枚举法求解
    bool partialEnumeration(const std::vector<std::vector<bool >> & b, std::vector<int>& x);

    // //保存可解的数据
    // void saveSolvableInfo(const std::vector<std::vector<bool> >&, const std::vector<std::vector<bool >> & );

    //获取用户当前总时间
    //int getTotalTime() const override;

    //生成提示数组
    void generateTipArray() override;

    //检验是否胜利
    bool isWin() const override;

    //判定难度
    QString judgeDiff() override;

    //计算经验
    unsigned calculateExp()override;

public slots:

    //------------------------公共槽----------------------------------

    //重写棋盘被点击的槽函数
    void onBoardClicked(int x, int y) override;

    //随机生成地图按钮被点击
    void onRandomBtnClicked() override;

};

#endif // LIGHTOUTGAME_H

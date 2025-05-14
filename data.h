#ifndef DATA_H
#define DATA_H

/*****************************************************************
 * class: Data （抽象游戏类）
 *
 * 用处: 获取游戏的数据信息、保存信息
 *****************************************************************/

#include <QDebug>
#include <QMap>
#include <QVector>
#include "config.h"
#include <QPoint>

class Data
{
public:

    //------------------------构造析构----------------------------------
    Data();
    ~Data();

    //------------------------公有方法----------------------------------

    //保存数据
    void saveData(int gameLevel, const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans);
    void saveData(int gameLevel, const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans, int step, int dir, QPoint pos);

    //------------------------公有属性----------------------------------

    //虫子所在位置 方向
    QMap<int, QPoint> m_bugPos;
    QMap<int, int> m_bugDir; //左上右下 0123

    //游戏数组
    QMap<int, QVector<QVector<bool>>> m_gameArray;

    //答案数组
    QMap<int, QVector<QVector<bool>>> m_ansArray;

    //步数数组
    int m_stepArray[ANTGAMENUMBER + 1]
    {
        0,
        1,
        5, 5, 5, 5, 5,
        20, 20, 20, 20, 20,
        50, 50, 50, 50, 50,
        100, 100, 100, 100, 100,
        200, 200, 200, 200, 200,
        300, 300, 300, 300, 300,
        500, 500, 500, 500, 500,
        1000
    };

private:

    //------------------------私有属性----------------------------------

    //记录关卡总数
    int m_antGameLevel = 0;
    int m_lightGameLevel = 0;

    //------------------------私有方法----------------------------------

    //从文件中读入数据
    void getData();

    //读取AntGame的数据
    void getAntGameData();

    //读取LightGame的数据
    void getLightGameData();

    //保存antData
    void saveAntData();

    //保存lightData
    void saveLightData();
};

#endif // DATA_H

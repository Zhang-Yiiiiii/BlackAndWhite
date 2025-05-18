#include "data.h"

#include <iostream>
#include <fstream>

//----------------------------------构造析构--------------------------------------------

Data::Data()
{
    getData();
}

Data::~Data()
{
    saveAntData();
    saveLightData();
}

//----------------------------------公有方法--------------------------------------------

//保存数据
void Data::saveData(int gameLevel, const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans)
{
    if(gameArray.empty())
    {
        return;
    }

    int rows = gameArray.size();
    int cols = gameArray[0].size();

    //将结果传给data
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            m_gameArray[gameLevel][i][j] = gameArray[i][j];
            m_ansArray[gameLevel][i][j] = ans[i][j];
        }
    }

    //保存至文件
    saveAntData();
    saveLightData();
}

void Data::saveData(int gameLevel, const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans, int step, int dir, QPoint pos)
{
    if(gameArray.empty())
    {
        return;
    }

    int rows = gameArray.size();
    int cols = gameArray[0].size();

    //将结果传给data
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            m_gameArray[gameLevel][i][j] = gameArray[i][j];
            m_ansArray[gameLevel][i][j] = ans[i][j];
        }
    }

    m_bugDir[gameLevel] = dir;
    m_bugPos[gameLevel] = pos;
    m_stepArray[gameLevel] = step;

    //保存至文件
    saveAntData();
    saveLightData();
}

//----------------------------------私有方法--------------------------------------------

//从文件中读取信息
//信息配置：
//兰顿蚂蚁：
// 关卡数
// 游戏步数
// 虫子的x 虫子的y 虫子的方向
// 20*20 的gameArray
// 20*20 的ansArray
//
//
//熄灯游戏
// 关卡数
// gameArray
// ansArray
//

//获取信息
void Data::getData()
{
    getAntGameData();
    getLightGameData();

    //保存至文件
    saveAntData();
    saveLightData();
}

void Data::getAntGameData()
{
    std::ifstream ifs(ANTDATAPATH, std::ios::in | std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    while (m_antGameLevel < ANTGAMENUMBER)
    {
        int gameLevel = 0, gameStep = 0, x = 0, y = 0, dir = 0;

        if (!ifs.read(reinterpret_cast<char*>(&gameLevel), sizeof(int)))
        {
            break;
        }

        if (!ifs.read(reinterpret_cast<char*>(&gameStep), sizeof(int)))
        {
            break;
        }

        if (!ifs.read(reinterpret_cast<char*>(&x), sizeof(int)))
        {
            break;
        }

        if (!ifs.read(reinterpret_cast<char*>(&y), sizeof(int)))
        {
            break;
        }

        if (!ifs.read(reinterpret_cast<char*>(&dir), sizeof(int)))
        {
            break;
        }

        QVector<QVector<bool>> v1(BOARDSIDELENGTH, QVector<bool>(BOARDSIDELENGTH)); //游戏数组
        QVector<QVector<bool>> v2(BOARDSIDELENGTH, QVector<bool>(BOARDSIDELENGTH)); //答案数组

        // 读取游戏数组
        for (int row = 0; row < BOARDSIDELENGTH; row++)
        {
            for (int col = 0; col < BOARDSIDELENGTH; col++)
            {
                bool val;
                ifs.read(reinterpret_cast<char*>(&val), sizeof(bool));
                v1[row][col] = val;
            }
        }

        // 读取答案数组
        for (int row = 0; row < BOARDSIDELENGTH; row++)
        {
            for (int col = 0; col < BOARDSIDELENGTH; col++)
            {
                bool val;
                ifs.read(reinterpret_cast<char*>(&val), sizeof(bool));
                v2[row][col] = val;
            }
        }

        m_stepArray[gameLevel] = gameStep;
        m_bugPos.insert(gameLevel, QPoint(x, y));
        m_bugDir.insert(gameLevel, dir);
        m_gameArray.insert(gameLevel, v1);
        m_ansArray.insert(gameLevel, v2);
        m_antGameLevel++;
    }

    ifs.close();
}

void Data::getLightGameData()
{
    std::ifstream ifs(LIGHTDATAPATH, std::ios::in | std::ios::binary);

    if (!ifs.is_open())
    {
        return;
    }

    while (m_lightGameLevel < LIGHTGAMEBUMBER)
    {
        int gameLevel = 0;

        if (!ifs.read(reinterpret_cast<char*>(&gameLevel), sizeof(int)))
        {
            break;
        }

        // if(gameLevel >= 48)
        // {
        // break;
        // }

        int rows = gameLevel - ANTGAMENUMBER + 3;
        int cols = gameLevel - ANTGAMENUMBER + 3;

        QVector<QVector<bool >> v1(rows, QVector<bool>(cols));  //游戏数组
        QVector<QVector<bool >> v2(rows, QVector<bool>(cols));  //答案数组

        // 读取游戏数组
        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                bool val;

                if (!ifs.read(reinterpret_cast<char*>(&val), sizeof(bool)))
                {
                    return;
                }

                v1[x][y] = val;
            }
        }

        // 读取答案数组
        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                bool val;

                if (!ifs.read(reinterpret_cast<char*>(&val), sizeof(bool)))
                {
                    return;
                }

                v2[x][y] = val;
            }
        }

        m_gameArray.insert(gameLevel, v1);
        m_ansArray.insert(gameLevel, v2);
        m_lightGameLevel++;
    }

    ifs.close();

    // 增加游戏关卡

    // int level = 48;

    // for(int i = 0; i < 5; i++)
    // {

    // int rows = level - ANTGAMENUMBER + 3;
    // int cols = level - ANTGAMENUMBER + 3;

    // QVector<QVector<bool >> v1(rows, QVector<bool>(cols, 1)); //游戏数组
    // QVector<QVector<bool >> v2(rows, QVector<bool>(cols, 1));  //答案数组

    // m_gameArray.insert(level, v1);
    // m_ansArray.insert(level, v2);

    // level++;
    // m_lightGameLevel++;

    // }

}

void Data::saveAntData()
{
    std::ofstream ofs(ANTDATAPATH, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!ofs.is_open())
    {
        return;
    }

    for (int i = 1; i <= m_antGameLevel; i++)
    {
        ofs.write(reinterpret_cast<char*>(&i), sizeof(i));  //关卡数
        ofs.write(reinterpret_cast<char*>(&m_stepArray[i]), sizeof(int));  //步数

        int x = m_bugPos[i].x();
        int y = m_bugPos[i].y();
        int dir = m_bugDir[i];

        ofs.write(reinterpret_cast<char*>(&x), sizeof(int));
        ofs.write(reinterpret_cast<char*>(&y), sizeof(int));
        ofs.write(reinterpret_cast<char*>(&dir), sizeof(int));

        // 写入游戏数组
        for (int row = 0; row < BOARDSIDELENGTH; row++)
        {
            for (int col = 0; col < BOARDSIDELENGTH; col++)
            {
                bool val = m_gameArray[i][row][col];
                ofs.write(reinterpret_cast<char*>(&val), sizeof(bool));
            }
        }

        // 写入答案数组
        for (int row = 0; row < BOARDSIDELENGTH; row++)
        {
            for (int col = 0; col < BOARDSIDELENGTH; col++)
            {
                bool val = m_ansArray[i][row][col];
                ofs.write(reinterpret_cast<char*>(&val), sizeof(bool));
            }
        }
    }

    ofs.close();
}

void Data::saveLightData()
{
    std::ofstream ofs(LIGHTDATAPATH, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!ofs.is_open())
    {
        return;
    }

    for (int i = 1; i <= m_lightGameLevel; i++)
    {
        int gameLevel = i + m_antGameLevel;
        ofs.write(reinterpret_cast<char*>(&gameLevel), sizeof(int)); // 写入关卡号

        int rows = i + 3;
        int cols = i + 3;

        // 写入游戏数组
        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                bool val = m_gameArray[gameLevel][x][y];
                ofs.write(reinterpret_cast<char*>(&val), sizeof(bool));
            }
        }

        // 写入答案数组
        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                bool val = m_ansArray[gameLevel][x][y];
                ofs.write(reinterpret_cast<char*>(&val), sizeof(bool));
            }
        }
    }

    ofs.close();
}

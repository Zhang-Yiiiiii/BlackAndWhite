#include "data.h"

#include <iostream>
#include <fstream>

Data::Data()
{
    getData();
}

//从文件中读取信息
//信息配置：
// 关卡数
// 游戏步数
// 虫子的x 虫子的y 虫子的方向
// 20*20 的gameArray
// 20*20 的ansArray

void Data::getData()
{
    getAntGameData();
    getLightGameData();
}

void Data::saveAntData()
{
    //输出 并且 清空文件所有内容的方式打开文件
    std::ofstream ofs(ANTDATAPATH, std::ios::out | std::ios::trunc);

    for (int i = 1; i <= m_antGameLevel; i++)
    {
        ofs << i << std::endl;
        ofs << m_stepArray[i] << std::endl;
        ofs << m_bugPos[i].x() << " " << m_bugPos[i].y() << " " << m_bugDir[i] << std::endl;

        for (int x = 0; x < BOARDSIDELENGTH; x++)
        {
            for (int y = 0; y < BOARDSIDELENGTH; y++)
            {
                ofs << m_gameArray[i][x][y] << " ";
            }

            ofs << std::endl;
        }

        for (int x = 0; x < BOARDSIDELENGTH; x++)
        {
            for (int y = 0; y < BOARDSIDELENGTH; y++)
            {
                ofs << m_ansArray[i][x][y] << " ";
            }

            ofs << std::endl;
        }
    }

    ofs.flush();
    ofs.close();
}

void Data::saveLightData()
{
    //输出 并且 清空文件所有内容的方式打开文件
    std::ofstream ofs(LIGHTDATAPATH, std::ios::out | std::ios::trunc);

    for (int i = 1; i <= m_lightGameLevel; i++)
    {
        ofs << i + m_antGameLevel << std::endl;
        int rows = i + 3;
        int cols = i + 3;

        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                ofs << m_gameArray[i + m_antGameLevel][x][y] << " ";
            }

            ofs << std::endl;
        }

        for (int x = 0; x < rows; x++)
        {
            for (int y = 0; y < cols; y++)
            {
                ofs << m_ansArray[i + m_antGameLevel][x][y] << " ";
            }

            ofs << std::endl;
        }
    }

    ofs.flush();
    ofs.close();
}

//析构函数
Data::~Data()
{
    saveAntData();
    saveLightData();
}

void Data::getAntGameData()
{

    //获取关卡数 步数 bug信息
    int gameLevel = 0;
    int gameStep = 0;
    int x, y, dir;

    std::ifstream ifs(ANTDATAPATH, std::ios::in);

    while (ifs >> gameLevel >> gameStep >> x >> y >> dir && m_antGameLevel < ANTGAMENUMBER)
    {
        int temp;

        // 初始化 v1 和 v2
        QVector<QVector<bool>> v1(BOARDSIDELENGTH, QVector<bool>(BOARDSIDELENGTH));
        QVector<QVector<bool>> v2(BOARDSIDELENGTH, QVector<bool>(BOARDSIDELENGTH));

        // 读取 gameArray
        for (int i = 0; i < BOARDSIDELENGTH; i++)
        {
            for (int j = 0; j < BOARDSIDELENGTH; j++)
            {
                ifs >> temp;
                v1[i][j] = temp;
            }
        }

        // 读取 ansArray
        for (int i = 0; i < BOARDSIDELENGTH; i++)
        {
            for (int j = 0; j < BOARDSIDELENGTH; j++)
            {
                ifs >> temp;
                v2[i][j] = temp;
            }
        }
        //将数据放入map容器
        m_stepArray[gameLevel] = gameStep;    //游戏步数
        m_bugPos.insert(gameLevel, QPoint(x, y)); //bug位置
        m_bugDir.insert(gameLevel, dir);  //bug方向

        m_gameArray.insert(gameLevel, v1); //游戏数组
        m_ansArray.insert(gameLevel, v2); //答案数组

        this->m_antGameLevel++;
    }

    ifs.close();
}

void Data::getLightGameData()
{

    //获取关卡数 步数 bug信息
    int gameLevel = 0;

    std::ifstream ifs(LIGHTDATAPATH, std::ios::in);

    while (ifs >> gameLevel && m_lightGameLevel < LIGHTGAMEBUMBER)
    {
        int temp;

        //棋盘的行列数
        int rows = gameLevel - ANTGAMENUMBER + 3;
        int cols = gameLevel - ANTGAMENUMBER + 3;

        // 初始化 v1 和 v2
        QVector<QVector<bool >> v1(rows, QVector<bool>(cols));
        QVector<QVector<bool >> v2(rows, QVector<bool>(cols));

        // 读取 gameArray
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ifs >> temp;
                v1[i][j] = temp;
            }
        }

        // 读取 ansArray
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ifs >> temp;
                v2[i][j] = temp;
            }
        }

        //将数据放入map容器
        m_gameArray.insert(gameLevel, v1); //游戏数组
        m_ansArray.insert(gameLevel, v2); //答案数组

        this->m_lightGameLevel++;
    }

    ifs.close();
}

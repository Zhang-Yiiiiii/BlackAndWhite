#include "data.h"

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

    int gameLevel = 0;
    int gameStep = 0;
    int x,y,dir;

    std::ifstream ifs(DATAPATH,std::ios::in);

    while (ifs >> gameLevel >> gameStep >> x >> y >> dir && totalLevel < SELECTBTNNUMBER)
    {
        int temp;

        // 初始化 v1 和 v2
        QVector<QVector<bool>> v1(20, QVector<bool>(20));
        QVector<QVector<bool>> v2(20, QVector<bool>(20));

        // 读取 gameArray
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                ifs >> temp;
                v1[i][j] = temp;
            }
        }

        // 读取 ansArray
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                ifs >> temp;
                v2[i][j] = temp;
            }
        }

        //将数据放入map容器
        stepArray[gameLevel] = gameStep;
        bugPos.insert(gameLevel,QPoint(x,y));
        bugDir.insert(gameLevel,dir);

        gameArray.insert(gameLevel,v1);
        ansArray.insert(gameLevel,v2);

        this->totalLevel++;
    }


    ifs.close();
}

//析构函数
Data::~Data()
{
    //输出 并且 清空文件所有内容的方式打开文件
    std::ofstream ofs(DATAPATH,std::ios::out | std::ios::trunc);

    for(int i=1;i<=totalLevel;i++)
    {
        ofs<<i<<std::endl;
        ofs<<stepArray[i]<<std::endl;
        ofs<<bugPos[i].x()<<" "<<bugPos[i].y()<<" "<<bugDir[i]<<std::endl;

        for(int x=0;x<20;x++)
        {
            for(int y=0;y<20;y++)
            {
                ofs<<gameArray[i][x][y]<<" ";
            }
            ofs<<std::endl;
        }

        for(int x=0;x<20;x++)
        {
            for(int y=0;y<20;y++)
            {
                ofs<<ansArray[i][x][y]<<" ";
            }
            ofs<<std::endl;
        }
    }

    ofs.flush();

    ofs.close();
}

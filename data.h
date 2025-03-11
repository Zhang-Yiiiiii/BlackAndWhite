#ifndef DATA_H
#define DATA_H

#include <QDebug>
#include <QMap>
#include <QVector>
#include "config.h"
#include <QPoint>
#include <iostream>
#include <fstream>

class Data
{
public:
    Data();

    //虫子所在位置 方向
    QMap<int,QPoint> bugPos;
    QMap<int,int> bugDir;  //左上右下 0123

    //游戏数组
    QMap<int,QVector<QVector<bool>>> gameArray;

    //答案数组
    QMap<int,QVector<QVector<bool>>> ansArray;

    //步数数组
    int stepArray[SELECTBTNNUMBER + 1]
        {
            0,
            1,
            5,5,5,5,5,
            20,20,20,20,20,
            50,50,50,50,50,
            100,100,100,100,100,
            200,200,200,200,200,
            300,300,300,300,300,
            500,500,500,500,500,
            1000
        };

    //从文件中读入数据
    void getData();

    //记录关卡总数
    int totalLevel = 0;

    //析构函数
    ~Data();

};

#endif // DATA_H

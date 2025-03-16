#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user.h"
#include "config.h"
#include <QString>
#include <fstream>
#include <QDebug>
#include <string>
#include <QVector>
#include <QMap>
#include <algorithm>
#include <QMessageBox>

class UserManager
{
public:
    UserManager();

    //记录用户人数
    int userNum;

    //用户数组指针
    User ** userArray;

    //添加用户的函数
    void addUser(QString userName, QString pwd);

    //保存到文件
    void save();

    //判断文件是否为空
    bool fileIsEmpty;

    //统计文件中用户的数量
    int getUserNum();

    //初始化用户
    void initUser();

    //对用户的通关时间进行排序
    void userSort(int level);

    //关卡的排序
    QVector<std::pair<QString,int>> rankList;

    //查找用户
    User* findUser(QString userName);

    //更新用户时间
    void updatePassTime(QString username ,int totalTime, int level);

    //验证用户信息 返回值等于1：用户不存在 2：密码错误 3：登录成功
    int verifyUserInfo(QString name,QString password);

    ~UserManager();

};

#endif // USERMANAGER_H

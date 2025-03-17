#ifndef USERMANAGER_H
#define USERMANAGER_H

/*
 * class: UserManager （用户管理者）
 *
 * 用处: 读取文件中的用户信息、修改用户通关记录、对关卡的最短通关时间排序
 *      将新信息保存进入文件
 */

#include "user.h"
#include <QString>
#include <QDebug>
#include <QVector>
#include <QMap>
#include <QMessageBox>

class UserManager
{
public:
    //构造和析构
    UserManager();
    ~UserManager();


    //关卡的排序
    QVector<std::pair<QString,int>> m_rankList;

    //添加用户的函数
    void addUser(QString userName, QString pwd);

    //对用户的通关时间进行排序
    void userSort(int level);

    //更新用户时间
    void updatePassTime(QString username ,int totalTime, int level);

    //验证用户信息 返回值等于1：用户不存在 2：密码错误 3：登录成功
    int verifyUserInfo(QString name,QString password);

private:
    //记录用户人数
    int m_userNum;

    //用户数组指针
    User ** m_userArray;

    //判断文件是否为空
    bool m_fileIsEmpty;

    //查找用户
    User* findUser(QString userName);

    //保存到文件
    void save();

    //统计文件中用户的数量
    int getUserNum();

    //初始化用户
    void initUser();

};

#endif // USERMANAGER_H

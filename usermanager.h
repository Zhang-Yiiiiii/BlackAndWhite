#ifndef USERMANAGER_H
#define USERMANAGER_H

/*****************************************************************
 * class: UserManager （用户管理者）
 *
 * 用处: 读取文件中的用户信息、修改用户通关记录、对关卡的最短通关时间排序
 *      将新信息保存进入文件
 *****************************************************************/

#include <QString>
#include <QDebug>
#include <QVector>
#include <QMap>
#include <QMessageBox>

#include "user.h"

class UserManager
{
public:
    //------------------------构造析构----------------------------------

    UserManager();
    ~UserManager();

    //------------------------公共属性----------------------------------

    //排行榜数组
    QVector<std::pair<QString, int>> m_rankList;

    //------------------------公共方法----------------------------------

    //验证用户信息 返回值等于1：用户不存在 2：密码错误 3：登录成功
    int verifyUserInfo(QString name, QString password);

    //判断用户名是否符合标准
    bool isUserNameRight(QString name);

    //判断密码是否符合标准
    bool isPassWordRight(QString pwd);

    //添加用户的函数
    bool addUser(QString userName, QString pwd);

    //对用户的通关时间进行排序
    UserManager* userSort(int level);

    //更新用户时间
    UserManager* updateUserTime(QString username, int totalTime, int level);

private:
    //------------------------私有属性----------------------------------

    //记录用户人数
    int m_userNum = 0;

    //用户数组指针
    User** m_userArray = nullptr;

    //判断文件是否为空
    bool m_fileIsEmpty = true;

    //------------------------私有方法----------------------------------

    //初始化用户
    UserManager* initUser();

    //统计文件中用户的数量
    int getUserNum() const;

    //查找用户
    User* findUser(QString userName) const;

    //保存到文件
    UserManager* save();

    //释放用户数组
    UserManager* releaseUserArray();
};

#endif // USERMANAGER_H

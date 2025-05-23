
// /*****************************************************************
// * class: UserManager （用户管理者）
// *
// * 用处: 读取文件中的用户信息、修改用户通关记录、对关卡的最短通关时间排序
// *      将新信息保存进入文件
// *****************************************************************/

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QVector>
#include <QMap>

#include "user.h"

class UserManager
{
public:

    //------------------------构造析构----------------------------------

    UserManager();
    ~UserManager();

    //------------------------公共方法----------------------------------

    // 登录验证：1 用户不存在，2 密码错误，3 登录成功
    int verifyUserInfo(const QString& name, const QString& password) const;

    bool isUserNameRight(const QString& name) const;
    bool isPassWordRight(const QString& pwd) const;

    bool addUser(const QString& userName, const QString& pwd);
    UserManager* updateUserTime(const QString& username, int totalTime, int level);
    UserManager* userSort(int level);
    User* findUser(const QString& userName) const;

    QVector<std::pair<QString, int>> m_rankList;

private:

    //------------------------私有属性----------------------------------

    QVector<User*> m_users;

    bool m_fileIsEmpty = true;

    //------------------------私有方法----------------------------------

    UserManager* loadFromFile();
    UserManager* saveToFile() const;
    void releaseUsers();
};

#endif // USERMANAGER_H

#ifndef USERUTILS_H
#define USERUTILS_H

#include "user.h"
#include <QList>

class UserUtils
{
public:
    // 根据用户名查找用户（返回指针，如果未找到返回 nullptr）
    static User* findUserByName(const QString& userName);

    static bool saveUsers(const QList<User*>& users, const QString& filePath = "userAvatar.txt");
    static QList<User*> loadUsers(const QString& filePath = "userAvatar.txt");
    static void saveSingleUser(User* user);
};

#endif // USERUTILS_H

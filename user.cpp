// #include "user.h"

// //----------------------------------构造析构--------------------------------------------

// User::User() {}

// //----------------------------------公共方法--------------------------------------------

// QString User::getUserName() const
// {
// return m_userName;
// }

// QString User::getUserPassword() const
// {
// return m_password;
// }

// User* User::setUserName(const QString& name)
// {
// m_userName = name;
// return this;
// }

// User* User::setUserPassword(const QString& password)
// {
// m_password = password;

// return this;
// }

// user.cpp
#include "user.h"

User::User() {}

QString User::getUserName() const
{

    return m_userName;
}

QString User::getUserPassword() const
{

    return m_password;
}

QString User::getAvatarPath() const
{

    return m_avatarPath;
}

User* User::setUserName(const QString& name)
{
    m_userName = name.left(nameMaxLen);
    return this;
}

User* User::setUserPassword(const QString& password)
{
    m_password = password;
    return this;
}

User* User::setAvatarPath(const QString& path)
{
    m_avatarPath = path;
    return this;
}

QString User::toTextLine() const
{

    return QString("%1,%2,%3").arg(m_userName, m_password, m_avatarPath);
}

User* User::fromTextLine(const QString& line)
{

    QStringList parts = line.split(",");

    if (parts.size() >= 3)
    {
        User* user = new User();
        user->setUserName(parts[0]);
        user->setUserPassword(parts[1]);
        user->setAvatarPath(parts[2]);
        return user;
    }

    return nullptr;
}

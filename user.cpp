#include "user.h"
#include "config.h"

//----------------------------------构造析构--------------------------------------------

User::User()
{
    for(int i = 0; i < SELECTBTNNUMBER; i++)
    {
        m_gameRecord[i + 1] = -1; //未通过此关
    }
}

//----------------------------------公共方法--------------------------------------------

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

QString User::getLevel() const
{
    return ScoreMap[m_level];
}

unsigned int User::getExp() const
{
    return m_exp;
}

void User::setExp(unsigned int exp)
{
    m_exp = exp;

    if(m_exp > expMax)
    {
        m_exp = expMax;
    }

}

void User::changeExp(unsigned change)
{
    setExp(m_exp + change);
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

User* User::setLevel(ScoreLevel lv)
{
    m_level = lv;
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

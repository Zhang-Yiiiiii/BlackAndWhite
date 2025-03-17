#include "user.h"

User::User()
{
    //初始化
    for(int i=0;i<SELECTBTNNUMBER;i++)
    {
        m_gameRecord[i+1] = -1;
    }
}

QString User::getUserName()
{
    return this->m_userName;
}

QString User::getUserPassword()
{
    return this->m_password;
}

void User::setUserName(QString name)
{
    this->m_userName = name;
}

void User::setUserPassword(QString pwd)
{
    this->m_password = pwd;
}

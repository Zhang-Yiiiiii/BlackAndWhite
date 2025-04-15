#include "user.h"
#include <QMessageBox>

User::User()
{
    //初始化
    for(int i = 0; i < SELECTBTNNUMBER; i++)
    {
        m_gameRecord[i + 1] = -1;
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

bool User::setUserName(QString name)
{
    //判断名字长度是否合适
    const int size = name.size();

    if(size > 0 && size <= 10)
    {
        this->m_userName = name;
        return true;
    }
    else
    {
        return false;
    }
}

bool User::setUserPassword(QString pwd)
{
    //判断密码长度是否合适
    const int size = pwd.size();

    if(size >= 6 && size <= 12)
    {
        this->m_password = pwd;
        return true;
    }
    else
    {
        return false;
    }

}

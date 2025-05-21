#include "user.h"
#include "config.h"
#include <QMessageBox>

//----------------------------------构造析构--------------------------------------------

User::User()
{
    //初始化
    for(int i = 0; i < SELECTBTNNUMBER; i++)
    {
        m_gameRecord[i + 1] = -1;
    }
}

//----------------------------------公共方法--------------------------------------------

QString User::getUserName() const
{
    return this->m_userName;
}

QString User::getUserPassword() const
{
    return this->m_password;
}

User* User::setUserName(QString name)
{
    //判断名字长度是否合适
    const int size = name.size();

    //if(size >= nameMinLen && size <= nameMaxLen)
    {
        this->m_userName = name;
    }

    return this;
}

User* User::setUserPassword(QString pwd)
{
    //判断密码长度是否合适
    const int size = pwd.size();

    //if(size >= pwdMinLen && size <= pwdMaxLen)
    {
        this->m_password = pwd;
    }

    return this;
}

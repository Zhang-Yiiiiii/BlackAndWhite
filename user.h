#ifndef USER_H
#define USER_H

/*
 * class: User （用户）
 *
 * 用处: 记录用户名和密码、记录用户通关记录
 *
 */

#include <QString>
#include <QMap>
#include "config.h"

class User
{
public:
    User();

    //获取用户名和密码
    QString getUserName();
    QString getUserPassword();

    //设置用户名和密码
    void setUserName(QString);
    void setUserPassword(QString);

    //游戏记录
    QMap<int,int> m_gameRecord;

private:
    //用户名
    QString m_userName = "";

    //密码
    QString m_password = "";

};

#endif // USER_H

#ifndef USER_H
#define USER_H

/*****************************************************************
 * class: User （用户）
 *
 * 用处: 记录用户名和密码、记录用户通关记录
 *
 *****************************************************************/

#include <QString>
#include <QMap>

class User
{
public:
    //------------------------构造析构----------------------------------

    User();

    //------------------------公共方法----------------------------------

    //获取用户名和密码
    QString getUserName() const;
    QString getUserPassword() const;

    //设置用户名和密码
    User* setUserName(QString);
    User* setUserPassword(QString);

    //------------------------公共属性----------------------------------

    //游戏记录
    QMap<int, int> m_gameRecord;    //关卡-最短通关时间

    static const int nameMinLen = 1;
    static const int nameMaxLen = 10;
    static const int pwdMinLen = 6;
    static const int pwdMaxLen = 12;

private:
    //------------------------私有属性----------------------------------

    //用户名
    QString m_userName = "";

    //密码
    QString m_password = "";

};

#endif // USER_H

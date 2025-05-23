// #ifndef USER_H
// #define USER_H

// /*****************************************************************
// * class: User （用户）
// *
// * 用处: 记录用户名和密码、记录用户通关记录
// *
// *****************************************************************/

// #include <QString>
// #include <QMap>
// #include <QDateTime>

// class User
// {
// public:
//     //------------------------构造析构----------------------------------
// User();

//     //------------------------公共方法----------------------------------
// QString getUserName() const;
// QString getUserPassword() const;

// User* setUserName(const QString& name);
// User* setUserPassword(const QString& password);

//     //------------------------公共属性----------------------------------
// QMap<int, int> m_gameRecord;

// static const int nameMinLen = 1;
// static const int nameMaxLen = 10;
// static const int pwdMinLen = 6;
// static const int pwdMaxLen = 12;

// private:
//     //------------------------私有属性----------------------------------
// QString m_userName = "";
// QString m_password = "";
// };

// #endif // USER_H

// user.h
#ifndef USER_H
#define USER_H

#include <QString>
#include <QMap>
#include <QDateTime>

class User
{
public:
    User();

    QString getUserName() const;
    QString getUserPassword() const;
    QString getAvatarPath() const;

    User* setUserName(const QString& name);
    User* setUserPassword(const QString& password);
    User* setAvatarPath(const QString& path);

    QString toTextLine() const;
    static User* fromTextLine(const QString& line);

    QMap<int, int> m_gameRecord;

    static const int nameMinLen = 1;
    static const int nameMaxLen = 10;
    static const int pwdMinLen = 6;
    static const int pwdMaxLen = 12;

private:
    QString m_userName = "";
    QString m_password = "";
    QString m_avatarPath = "";
};

#endif // USER_H

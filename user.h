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
#include <QDateTime>

//评分等级
enum ScoreLevel
{
    S,
    A,
    B,
    C,
    D
};

const QMap<ScoreLevel, QString> ScoreMap
{
    {S, "S"},
    {A, "A"},
    {B, "B"},
    {C, "C"},
    {D, "D"},
};

class User
{
public:
    //------------------------构造析构----------------------------------
    User();
    User(QString name, QString pwd);

    //------------------------公共方法----------------------------------

    QString getUserName() const;
    QString getUserPassword() const;
    QString getAvatarPath() const;
    QString getLevel() const;
    unsigned getExp() const ;

    User* setUserName(const QString& name);
    User* setUserPassword(const QString& password);
    User* setAvatarPath(const QString& path);
    User* setLevel(ScoreLevel lv);
    void setExp(unsigned exp);
    void changeExp(unsigned change);

    QString toTextLine() const;
    static User* fromTextLine(const QString& line);

    //------------------------公共属性----------------------------------
    QMap<int, int> m_gameRecord;

    static const int nameMinLen = 0;
    static const int nameMaxLen = 20;
    static const int pwdMinLen = 6;
    static const int pwdMaxLen = 12;
    static const unsigned expMax = 999999;

private:

    //------------------------私有属性----------------------------------
    QString m_userName = "";
    QString m_password = "";
    QString m_avatarPath = ":/image/default_avatar.png";
    unsigned m_exp = 0;
    ScoreLevel m_level = D;

};

#endif // USER_H

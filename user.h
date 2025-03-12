#ifndef USER_H
#define USER_H

#include <QString>
#include <QMap>

class User
{
public:
    User();


    //用户名
    QString userName = "";

    //密码
    QString password = "";

    //游戏记录
    QMap<int,int> gameRecord;

};

#endif // USER_H

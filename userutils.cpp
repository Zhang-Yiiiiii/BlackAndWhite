#include "userutils.h"
#include <QFile>
#include <QTextStream>

User* UserUtils::findUserByName(const QString& userName)
{
    QList<User*> users = loadUsers();

    User* user = nullptr;

    for (User* u : users)
    {
        if (u->getUserName() == userName)
        {
            user = u;
            break;
        }
    }

    if(user == nullptr && userName == "default")    //找的是默认用户
    {
        user = new User("default", "default");
        saveSingleUser(user);
    }

    return user;
}

bool UserUtils::saveUsers(const QList<User*>& users, const QString& filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream out(&file);

    for (User* user : users)
    {
        out << user->toTextLine() << "\n";
    }

    file.close();
    return true;
}

QList<User*> UserUtils::loadUsers(const QString& filePath)
{
    QList<User*> users;
    QFile file(filePath);
    qDebug() << filePath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return users;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (!line.isEmpty())
        {
            User* user = User::fromTextLine(line);

            if (user)
            {
                users.append(user);
            }
        }
    }

    file.close();

    return users;
}

void UserUtils::saveSingleUser(User* currentUser)
{
    if(currentUser == nullptr)
    {
        return ;
    }

    QList<User*> list = loadUsers();
    bool updated = false;

    for (int i = 0; i < list.size(); ++i)
    {
        if (list[i]->getUserName() == currentUser->getUserName())
        {
            list[i] = currentUser;
            updated = true;
            break;
        }
    }

    if (!updated)
    {
        list.append(currentUser);
    }

    saveUsers(list);
}

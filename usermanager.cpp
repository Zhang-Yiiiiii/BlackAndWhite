#include "usermanager.h"

#include "config.h"
#include <fstream>
#include <string>
#include <algorithm>

UserManager::UserManager()
{
    std::ifstream ifs(USERDATAPATH, std::ios::in);

    //文件不存在
    if(!ifs.is_open())
    {
        qDebug() << QString("文件不存在").arg(USERDATAPATH);

        this->m_userNum = 0;
        this->m_userArray = nullptr;
        this->m_fileIsEmpty = true;

        ifs.close();
        return;
    }

    //文件存在但为空
    char ch;
    ifs >> ch;

    if(ifs.eof())
    {
        qDebug() << QString("文件为空").arg(USERDATAPATH);

        this->m_userNum = 0;
        this->m_userArray = nullptr;
        this->m_fileIsEmpty = true;

        ifs.close();
        return;
    }

    //文件存在，记录数据
    this->m_userNum = getUserNum();
    this->m_userArray = new User * [this->m_userNum];
    this->initUser();

    ifs.close();
}

void UserManager::addUser(QString userName, QString pwd)
{
    //用户人数加1
    this->m_userNum++;

    //开辟新空间
    User** newSpace = new User* [this->m_userNum];

    //拷贝旧数据
    for(int i = 0; i < this->m_userNum - 1; i++)
    {
        newSpace[i] = this->m_userArray[i];
    }

    //添加新数据
    User * newUser = new User;
    newUser->setUserName(userName);
    newUser->setUserPassword(pwd);

    newSpace[this->m_userNum - 1] = newUser;

    //释放原有空间
    releaseUserArray();
    //更改新空间指向
    this->m_userArray = newSpace;

    //保存到文件
    this->save();
    this->m_fileIsEmpty = false;
}

void UserManager::save()
{
    std::ofstream ofs(USERDATAPATH, std::ios::out);

    for(int i = 0; i < this->m_userNum; i++)
    {

        ofs << this->m_userArray[i]->getUserName().toStdString() << " "
            << this->m_userArray[i]->getUserPassword().toStdString() << std::endl;

        QMap<int, int>::iterator it;

        for (it = this->m_userArray[i]->m_gameRecord.begin(); it != this->m_userArray[i]->m_gameRecord.end(); it++)
        {
            ofs << it.key() << " " << it.value() << std::endl;
        }
    }

    ofs.close();
}

int UserManager::getUserNum()
{
    //记录用户人数
    int cnt = 0;

    std::ifstream ifs(USERDATAPATH, std::ios::in);

    std::string name;
    std::string pwd;

    while(ifs >> name && ifs >> pwd)
    {
        //读取用户记录
        for(int i = 0; i < SELECTBTNNUMBER; i++)
        {
            int level;
            int record;

            ifs >> level;
            ifs >> record;
        }

        cnt++;
    }

    ifs.close();

    return cnt;
}

void UserManager::initUser()
{
    std::ifstream ifs(USERDATAPATH, std::ios::in);

    std::string name;
    std::string pwd;

    int index = 0;  //用于添加用户

    //读取用户名和密码
    while(ifs >> name && ifs >> pwd)
    {
        User * user = new User;
        user->setUserName(QString::fromStdString(name));
        user->setUserPassword(QString::fromStdString(pwd));

        //读取用户记录
        for(int i = 0; i < SELECTBTNNUMBER; i++)
        {
            int level;
            int record;

            ifs >> level;
            ifs >> record;

            user->m_gameRecord[level] = record;
        }

        this->m_userArray[index++] = user;
    }

    ifs.close();
}

void UserManager::releaseUserArray()
{
    if(m_userArray)
    {
        for(int i = 0; i < m_userNum; i++)
        {
            if(m_userArray[i])
            {
                delete m_userArray[i];
                m_userArray[i] = nullptr;
            }
        }

        delete[] m_userArray;
        m_userArray = nullptr;
    }
}

void UserManager::userSort(int level)
{
    QString name;
    int record;

    m_rankList.clear();

    //将指定关卡的数据放入容器
    for(int i = 0; i < m_userNum; i++)
    {
        name = this->m_userArray[i]->getUserName();
        record = this->m_userArray[i]->m_gameRecord[level];

        if(record == -1)
        {
            continue;    //用户没有通关
        }

        this->m_rankList.push_back(std::pair<QString, int>(name, record));
    }

    //对容器进行排序
    std::sort(m_rankList.begin(), m_rankList.end(), [](const std::pair<QString, int>& a, const std::pair<QString, int>& b)
    {
        if (a.second == b.second)
        {
            return a.first < b.first; // 如果 record 相同，按名字排序
        }

        return a.second < b.second; // 按 int 排序
    });
}

User* UserManager::findUser(QString userName)
{
    User * user = nullptr;

    for(int i = 0; i < m_userNum; i++)
    {
        if(m_userArray[i]->getUserName() == userName)
        {
            user = m_userArray[i];
        }
    }

    return user;
}

void UserManager::updateTotalTime(QString username, int totalTime, int level)
{
    User * user = findUser(username);

    //没有登录 或者没有找到用户
    if(user == nullptr)
    {
        return;
    }

    int minTotalTime = 0;

    if(user->m_gameRecord[level] == -1)  //用户是第一次通关
    {
        minTotalTime = totalTime;
    }
    else
    {
        minTotalTime = std::min(user->m_gameRecord[level], totalTime);
    }

    user->m_gameRecord[level] = minTotalTime;
    this->save();
}

int UserManager::verifyUserInfo(QString name, QString password)
{
    //验证用户信息

    //返回值 1：不存在用户  2：密码错误  3：登录成功
    for(int i = 0; i < this->m_userNum; i++)
    {
        QString tempName = this->m_userArray[i]->getUserName();
        QString tempPwd = this->m_userArray[i]->getUserPassword();

        if(tempName == name && tempPwd == password)
        {
            return 3;  //成功找到
        }
        else if(tempName == name && tempPwd != password)
        {
            return 2;  //密码错误
        }
    }

    return 1;  //未找到用户
}

UserManager::~UserManager()
{
    this->save();

    releaseUserArray();
}

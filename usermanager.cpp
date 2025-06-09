// #include "usermanager.h"

// #include "config.h"
// #include <fstream>
// #include <algorithm>

// //----------------------------------构造析构--------------------------------------------

// UserManager::UserManager()
// {

// qDebug() << m_userNum;
// std::ifstream ifs(USERDATAPATH, std::ios::in | std::ios::binary);

// if (!ifs.is_open())
// {
// qDebug() << "文件不存在:" << USERDATAPATH;
// m_userNum = 0;
// m_userArray = nullptr;
// m_fileIsEmpty = true;
// return;
// }

//     // 判断文件是否为空
//     // 判断文件是否为空
// ifs.seekg(0, std::ios::end);

// if (ifs.tellg() == 0)
// {
// qDebug() << "文件为空:" << USERDATAPATH;
// m_userNum = 0;
// m_userArray = nullptr;
// m_fileIsEmpty = true;
// return;
// }

// ifs.seekg(0, std::ios::beg); // 重置到文件开头
// ifs.close();

// initUser();               // 初始化用户
// m_fileIsEmpty = false;
// }

// UserManager::~UserManager()
// {
// this->save();

// releaseUserArray();
// }

// //----------------------------------公共方法--------------------------------------------

// //验证用户信息
// int UserManager::verifyUserInfo(QString name, QString password)
// {
//     //返回值 1：不存在用户  2：密码错误  3：登录成功
// for(int i = 0; i < this->m_userNum; i++)
// {
// QString tempName = this->m_userArray[i]->getUserName();
// QString tempPwd = this->m_userArray[i]->getUserPassword();

// if(tempName == name && tempPwd == password)
// {
// return 3;  //成功找到
// }
// else if(tempName == name && tempPwd != password)
// {
// return 2;  //密码错误
// }
// }

// return 1;  //未找到用户
// }

// //判断用户名格式
// bool UserManager::isUserNameRight(QString name)
// {
// const unsigned int size = name.size();

//     //用户名长度 1-10
// const int minLen = 0;
// const int maxLen = 10;

// if(size > minLen && size <= maxLen)
// {
// return true;
// }

// return false;
// }

// //判断密码格式
// bool UserManager::isPassWordRight(QString pwd)
// {
// const unsigned int size = pwd.size();

//     //密码长度 6-12
// const int minLen = 6;
// const int maxLen = 12;

// if(size >= minLen && size <= maxLen)
// {
// return true;
// }

// return false;
// }

// //添加用户
// bool UserManager::addUser(QString userName, QString pwd)
// {
// if(verifyUserInfo(userName, pwd) != 1) //找到了用户
// {
// return false;   //用户已存在
// }

//     //判断添加是否合理
// if(!this->isUserNameRight(userName))
// {
// return false;
// }

// if(!this->isPassWordRight(pwd))
// {
// return false;
// }

//     //新用户
// User * newUser = new User;

//     //开辟新空间
// User** newSpace = new User* [m_userNum + 1];

//     //拷贝旧数据
// for(int i = 0; i < m_userNum; i++)
// {
// newSpace[i] = m_userArray[i];
// }

// newSpace[m_userNum] = newUser;

//     //释放原有空间
// User** oldArray = m_userArray;
// m_userArray = newSpace;
// delete[] oldArray; // 仅释放旧数组内存，不删除User对象

//     //用户人数加1
// m_userNum++;    //在释放空间之后增加，不然释放会越界

//     //保存到文件
// this->save();
// m_fileIsEmpty = false;

// return true;
// }

// //对用户排序
// UserManager* UserManager::userSort(int level)
// {
// QString name;
// int record;

// m_rankList.clear();

//     //将指定关卡的数据放入容器
// for(int i = 0; i < m_userNum; i++)
// {
// name = m_userArray[i]->getUserName();
// record = m_userArray[i]->m_gameRecord[level];

// if(record == -1)
// {
// continue;    //用户没有通关
// }

// this->m_rankList.push_back(std::pair<QString, int>(name, record));
// }

//     //对容器进行排序
// std::sort(m_rankList.begin(), m_rankList.end(), [](const std::pair<QString, int>& a, const std::pair<QString, int>& b)
// {
// if (a.second == b.second)
// {
// return a.first < b.first; // 如果 record 相同，按名字排序
// }

// return a.second < b.second; // 按 int 排序
// });

// return this;
// }

// //更新时间
// UserManager* UserManager::updateUserTime(QString username, int totalTime, int level)
// {
// User * user = findUser(username);

//     //没有登录 或者没有找到用户
// if(user == nullptr)
// {
// return this;
// }

// int minTotalTime = 0;

// if(user->m_gameRecord[level] == -1)  //用户是第一次通关
// {
// minTotalTime = totalTime;
// }
// else
// {
// minTotalTime = std::min(user->m_gameRecord[level], totalTime);
// }

// user->m_gameRecord[level] = minTotalTime;
// this->save();

// return this;
// }

// //----------------------------------私有方法--------------------------------------------

// //初始化用户
// // UserManager* UserManager::initUser()
// // {
// // std::ifstream ifs(USERDATAPATH, std::ios::binary);

// //     //读取用户人数
// // ifs.read(reinterpret_cast<char*>(&m_userNum), sizeof(int));
// // m_userArray = new User*[m_userNum];

// // for (int i = 0; i < m_userNum; ++i)
// // {
// //         // 读取用户名
// // int nameLen;
// // ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
// // char* nameBuf = new char[nameLen + 1];
// // ifs.read(nameBuf, nameLen);
// // nameBuf[nameLen] = '\0';

// //         // 读取密码
// // int pwdLen;
// // ifs.read(reinterpret_cast<char*>(&pwdLen), sizeof(int));
// // char* pwdBuf = new char[pwdLen + 1];
// // ifs.read(pwdBuf, pwdLen);
// // pwdBuf[pwdLen] = '\0';

// //         // 创建用户对象并设置信息
// // User* user = new User;
// // user->setUserName(QString(nameBuf));
// // user->setUserPassword(QString(pwdBuf));
// // delete[] nameBuf;
// // delete[] pwdBuf;

// //         // 读取记录数
// // int recordCount;
// // ifs.read(reinterpret_cast<char*>(&recordCount), sizeof(int));

// // for (int j = 0; j < recordCount; ++j)
// // {
// // int key, val;
// // ifs.read(reinterpret_cast<char*>(&key), sizeof(int));
// // ifs.read(reinterpret_cast<char*>(&val), sizeof(int));
// // user->m_gameRecord[key] = val;
// // }

// // m_userArray[i] = user;
// // }

// // return this;
// // }

// //----------------------------------初始化用户修改----------------------------------------
// UserManager* UserManager::initUser()
// {
// std::ifstream ifs(USERDATAPATH, std::ios::binary);

//     // 读取用户人数
// ifs.read(reinterpret_cast<char*>(&m_userNum), sizeof(int));
// m_userArray = new User*[m_userNum];

// for (int i = 0; i < m_userNum; ++i)
// {
//         // 读取用户名
// int nameLen;
// ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(int));

// QByteArray nameBytes;
// nameBytes.resize(nameLen);
// ifs.read(nameBytes.data(), nameLen); // 关键修改：精确读取指定长度

//         // 读取密码
// int pwdLen;
// ifs.read(reinterpret_cast<char*>(&pwdLen), sizeof(int));

// QByteArray pwdBytes;
// pwdBytes.resize(pwdLen);
// ifs.read(pwdBytes.data(), pwdLen);

//         // 创建用户
// User* user = new User;
// user->setUserName(QString::fromUtf8(nameBytes)); // 自动处理编码
// user->setUserPassword(QString::fromUtf8(pwdBytes));

//         // 读取游戏记录（保持原有逻辑）
// int recordCount;
// ifs.read(reinterpret_cast<char*>(&recordCount), sizeof(int));

// for (int j = 0; j < recordCount; ++j)
// {
// int key, val;
// ifs.read(reinterpret_cast<char*>(&key), sizeof(int));
// ifs.read(reinterpret_cast<char*>(&val), sizeof(int));
// user->m_gameRecord[key] = val;
// }

// m_userArray[i] = user;
// }

// return this;

// ifs.close();
// }

// //获取用户人数
// int UserManager::getUserNum() const
// {
// return m_userNum;
// }

// //查找用户
// User* UserManager::findUser(QString userName) const
// {
// User * user = nullptr;

// for(int i = 0; i < m_userNum; i++)
// {
// if(m_userArray[i]->getUserName() == userName)
// {
// user = m_userArray[i];
// }
// }

// return user;
// }

// //保存信息到文件
// UserManager* UserManager::save()
// {
// std::ofstream ofs(USERDATAPATH, std::ios::out | std::ios::binary | std::ios::trunc);

// if (!ofs.is_open())
// {
// return this;
// }

//     //用户人数
// ofs.write(reinterpret_cast<const char*>(&m_userNum), sizeof(int));

// for (int i = 0; i < m_userNum; ++i)
// {
//         // 保存用户名
// QByteArray nameData = m_userArray[i]->getUserName().toUtf8();
// int nameLen = nameData.size();
// ofs.write(reinterpret_cast<char*>(&nameLen), sizeof(int));
// ofs.write(nameData.data(), nameLen);

//         // 保存密码
// QByteArray pwdData = m_userArray[i]->getUserPassword().toUtf8();
// int pwdLen = pwdData.size();
// ofs.write(reinterpret_cast<char*>(&pwdLen), sizeof(int));
// ofs.write(pwdData.data(), pwdLen);

//         // 保存游戏记录条数
// int recordCount = m_userArray[i]->m_gameRecord.size();
// ofs.write(reinterpret_cast<char*>(&recordCount), sizeof(int));

//         // 保存游戏记录键值对
// for (auto it = m_userArray[i]->m_gameRecord.begin(); it != m_userArray[i]->m_gameRecord.end(); ++it)
// {
// int key = it.key();
// int val = it.value();
// ofs.write(reinterpret_cast<char*>(&key), sizeof(int));
// ofs.write(reinterpret_cast<char*>(&val), sizeof(int));
// }
// }

// ofs.flush();

// ofs.close();

// return this;
// }

// //释放内存
// UserManager* UserManager::releaseUserArray()
// {
// if(m_userArray)
// {
// for(int i = 0; i < m_userNum; i++)
// {
// if(m_userArray[i])
// {
// delete m_userArray[i];
// m_userArray[i] = nullptr;
// }
// }

// delete[] m_userArray;
// m_userArray = nullptr;
// m_userNum = 0;
// }

// return this;
// }

#include "usermanager.h"
#include "config.h"

#include <QFile>
#include <QDebug>
#include <fstream>
#include <algorithm>

//----------------------------------构造析构--------------------------------------------
UserManager::UserManager()
{
    QFile file(USERDATAPATH);
    m_fileIsEmpty = !file.exists() || file.size() == 0;

    if (!m_fileIsEmpty)
    {
        loadFromFile();
    }

    User* u = findUser("default");   //查找是否存在默认用户

    if(!u)
    {
        addUser("default", "default");  //没有就添加
    }
}

// 析构：释放用户并保存
UserManager::~UserManager()
{
    saveToFile();
    releaseUsers();
}

// 用户验证
int UserManager::verifyUserInfo(const QString& name, const QString& password) const
{
    for (const User* user : m_users)
    {
        if (user->getUserName() == name)
        {
            return (user->getUserPassword() == password) ? 3 : 2;
        }
    }

    return 1;
}

bool UserManager::isUserNameRight(const QString& name) const
{
    return !name.isEmpty() && name.size() <= 10;
}

bool UserManager::isPassWordRight(const QString& pwd) const
{
    return pwd.size() >= 6 && pwd.size() <= 12;
}

//----------------------------------公共方法--------------------------------------------

bool UserManager::addUser(const QString& userName, const QString& pwd)
{
    if (verifyUserInfo(userName, pwd) != 1 || !isUserNameRight(userName) || !isPassWordRight(pwd))
    {
        return false;
    }

    User* newUser = new User;
    newUser->setUserName(userName);
    newUser->setUserPassword(pwd);
    m_users.push_back(newUser);

    saveToFile();
    m_fileIsEmpty = false;
    return true;
}

UserManager* UserManager::updateUserTime(const QString& username, int totalTime, int level)
{
    User* user = findUser(username);

    if (!user)
    {
        return this;
    }

    int& record = user->m_gameRecord[level];
    record = (record == -1) ? totalTime : std::min(record, totalTime);
    saveToFile();
    return this;
}

UserManager* UserManager::userSort(int level)
{
    m_rankList.clear();

    for (const User* user : m_users)
    {
        int time = user->m_gameRecord.value(level, -1);

        if (time != -1)
        {
            m_rankList.emplace_back(user->getUserName(), time);
        }
    }

    std::sort(m_rankList.begin(), m_rankList.end(),
              [](const auto & a, const auto & b)
    {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    return this;
}

User* UserManager::findUser(const QString& userName) const
{
    for (User* user : m_users)
    {
        if (user->getUserName() == userName)
        {
            return user;
        }
    }

    return nullptr;
}

void UserManager::addExp(User *user, unsigned int change)
{
    user->changeExp(change);
    updateLV(user);
}

//----------------------------------私有方法--------------------------------------------

// 加载用户
UserManager* UserManager::loadFromFile()
{
    std::ifstream ifs(USERDATAPATH, std::ios::binary);

    if (!ifs)
    {
        return this;
    }

    int userCount;
    ifs.read(reinterpret_cast<char*>(&userCount), sizeof(int));

    for (int i = 0; i < userCount; ++i)
    {
        int nameLen, pwdLen;
        ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
        QByteArray nameData(nameLen, 0);
        ifs.read(nameData.data(), nameLen);

        ifs.read(reinterpret_cast<char*>(&pwdLen), sizeof(int));
        QByteArray pwdData(pwdLen, 0);
        ifs.read(pwdData.data(), pwdLen);

        User* user = new User;
        user->setUserName(QString::fromUtf8(nameData));
        user->setUserPassword(QString::fromUtf8(pwdData));

        //读入经验
        unsigned exp;
        ifs.read(reinterpret_cast<char*>(&exp), sizeof(int));
        user->setExp(exp);

        int recordCount;
        ifs.read(reinterpret_cast<char*>(&recordCount), sizeof(int));

        for (int j = 0; j < recordCount; ++j)
        {
            int key, val;
            ifs.read(reinterpret_cast<char*>(&key), sizeof(int));
            ifs.read(reinterpret_cast<char*>(&val), sizeof(int));
            user->m_gameRecord[key] = val;
        }

        m_users.push_back(user);
    }

    updateAllLv();  //更新所有用户等级

    return this;
}

// 保存用户
UserManager* UserManager::saveToFile() const
{
    std::ofstream ofs(USERDATAPATH, std::ios::binary | std::ios::trunc);

    if (!ofs)
    {
        return nullptr;
    }

    int userCount = m_users.size();
    ofs.write(reinterpret_cast<const char*>(&userCount), sizeof(int));

    for (const User* user : m_users)
    {
        QByteArray nameData = user->getUserName().toUtf8();
        int nameLen = nameData.size();
        ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(int));
        ofs.write(nameData.data(), nameLen);

        QByteArray pwdData = user->getUserPassword().toUtf8();
        int pwdLen = pwdData.size();
        ofs.write(reinterpret_cast<const char*>(&pwdLen), sizeof(int));
        ofs.write(pwdData.data(), pwdLen);

        //写入经验
        unsigned exp = user->getExp();
        ofs.write(reinterpret_cast<const char*>(&exp), sizeof(int));

        int recordCount = user->m_gameRecord.size();
        ofs.write(reinterpret_cast<const char*>(&recordCount), sizeof(int));

        for (auto it = user->m_gameRecord.begin(); it != user->m_gameRecord.end(); ++it)
        {
            int key = it.key();
            int val = it.value();
            ofs.write(reinterpret_cast<const char*>(&key), sizeof(int));
            ofs.write(reinterpret_cast<const char*>(&val), sizeof(int));
        }
    }

    return const_cast<UserManager*>(this);
}

// 内存清理
void UserManager::releaseUsers()
{
    for (User* user : m_users)
    {
        delete user;
    }

    m_users.clear();
}

//更新等级
void UserManager::updateLV(User* user)
{
    unsigned exp = user->getExp();
    unsigned lvArray[] {2000, 5000, 10000, 100000, 999999};

    for(int i = 0; i < 5; i++)
    {
        if(exp <= lvArray[i])
        {
            user->setLevel(static_cast<ScoreLevel>(5 - i - 1));
            return ;
        }
    }
}

//更新所有所有等级
void UserManager::updateAllLv()
{
    for(User* user : m_users)
    {
        updateLV(user);
    }
}

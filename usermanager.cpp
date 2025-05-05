#include "usermanager.h"

#include "config.h"
#include <fstream>
#include <algorithm>

UserManager::UserManager()
{
    std::ifstream ifs(USERDATAPATH, std::ios::in | std::ios::binary);

    if (!ifs.is_open())
    {
        qDebug() << "文件不存在:" << USERDATAPATH;
        m_userNum = 0;
        m_userArray = nullptr;
        m_fileIsEmpty = true;
        return;
    }

    // 判断文件是否为空
    ifs.seekg(0, std::ios::end);
    std::streampos fileSize = ifs.tellg();

    if (fileSize == 0)
    {
        qDebug() << "文件为空:" << USERDATAPATH;
        m_userNum = 0;
        m_userArray = nullptr;
        m_fileIsEmpty = true;
        return;
    }

    ifs.seekg(0, std::ios::beg); // 重置到文件开头
    ifs.close();

    initUser();               // 调用新的封装方法读取数据
    m_fileIsEmpty = false;
}

//验证用户信息
int UserManager::verifyUserInfo(QString name, QString password)
{
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

//判断用户名格式
bool UserManager::isUserNameRight(QString name)
{
    const unsigned int size = name.size();

    //用户名长度 1-10
    if(size > 0 && size <= 10)
    {
        return true;
    }

    return false;
}

//判断密码格式
bool UserManager::isPassWordRight(QString pwd)
{
    const unsigned int size = pwd.size();

    //密码长度 6-12
    if(size >= 6 && size <= 12)
    {
        return true;
    }

    return false;
}

//添加用户
bool UserManager::addUser(QString userName, QString pwd)
{
    if(verifyUserInfo(userName, pwd) != 1) //找到了用户
    {
        return false;   //用户已存在
    }

    //新用户
    User * newUser = new User;

    //判断添加是否合理
    if(!this->isUserNameRight(userName))
    {
        delete newUser;
        newUser = nullptr;
        return false;
    }

    if(!this->isPassWordRight(pwd))
    {
        delete newUser;
        newUser = nullptr;
        return false;
    }

    //用户人数加1
    this->m_userNum++;

    //开辟新空间
    User** newSpace = new User* [this->m_userNum];

    //拷贝旧数据
    for(int i = 0; i < this->m_userNum - 1; i++)
    {
        newSpace[i] = this->m_userArray[i];
    }

    newSpace[this->m_userNum - 1] = newUser;

    //释放原有空间
    releaseUserArray();

    //更改新空间指向
    this->m_userArray = newSpace;

    //保存到文件
    this->save();
    this->m_fileIsEmpty = false;

    return true;
}

//保存信息到文件
void UserManager::save() const
{
    std::ofstream ofs(USERDATAPATH, std::ios::out | std::ios::binary);

    if (!ofs.is_open())
    {
        return;
    }

    //用户人数
    ofs.write(reinterpret_cast<const char*>(&m_userNum), sizeof(int));

    for (int i = 0; i < m_userNum; ++i)
    {
        // 保存用户名
        QByteArray nameData = m_userArray[i]->getUserName().toUtf8();
        int nameLen = nameData.size();
        ofs.write(reinterpret_cast<char*>(&nameLen), sizeof(int));
        ofs.write(nameData.data(), nameLen);

        // 保存密码
        QByteArray pwdData = m_userArray[i]->getUserPassword().toUtf8();
        int pwdLen = pwdData.size();
        ofs.write(reinterpret_cast<char*>(&pwdLen), sizeof(int));
        ofs.write(pwdData.data(), pwdLen);

        // 保存游戏记录条数
        int recordCount = m_userArray[i]->m_gameRecord.size();
        ofs.write(reinterpret_cast<char*>(&recordCount), sizeof(int));

        // 保存游戏记录键值对
        for (auto it = m_userArray[i]->m_gameRecord.begin(); it != m_userArray[i]->m_gameRecord.end(); ++it)
        {
            int key = it.key();
            int val = it.value();
            ofs.write(reinterpret_cast<char*>(&key), sizeof(int));
            ofs.write(reinterpret_cast<char*>(&val), sizeof(int));
        }
    }

    ofs.close();
}

//获取用户人数
int UserManager::getUserNum() const
{
    return m_userNum;
}

//初始化用户
void UserManager::initUser()
{
    std::ifstream ifs(USERDATAPATH, std::ios::in | std::ios::binary);

    //读取用户人数
    ifs.read(reinterpret_cast<char*>(&m_userNum), sizeof(int));
    m_userArray = new User*[m_userNum];

    for (int i = 0; i < m_userNum; ++i)
    {
        // 读取用户名
        int nameLen;
        ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(int));
        char* nameBuf = new char[nameLen + 1];
        ifs.read(nameBuf, nameLen);
        nameBuf[nameLen] = '\0';

        // 读取密码
        int pwdLen;
        ifs.read(reinterpret_cast<char*>(&pwdLen), sizeof(int));
        char* pwdBuf = new char[pwdLen + 1];
        ifs.read(pwdBuf, pwdLen);
        pwdBuf[pwdLen] = '\0';

        // 创建用户对象并设置信息
        User* user = new User;
        user->setUserName(QString::fromUtf8(nameBuf));
        user->setUserPassword(QString::fromUtf8(pwdBuf));
        delete[] nameBuf;
        delete[] pwdBuf;

        // 读取记录数
        int recordCount;
        ifs.read(reinterpret_cast<char*>(&recordCount), sizeof(int));

        for (int j = 0; j < recordCount; ++j)
        {
            int key, val;
            ifs.read(reinterpret_cast<char*>(&key), sizeof(int));
            ifs.read(reinterpret_cast<char*>(&val), sizeof(int));
            user->m_gameRecord[key] = val;
        }

        m_userArray[i] = user;
    }
}

//释放内存
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

//对用户排序
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

//查找用户
User* UserManager::findUser(QString userName) const
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

//更新时间
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

UserManager::~UserManager()
{
    this->save();

    releaseUserArray();
}

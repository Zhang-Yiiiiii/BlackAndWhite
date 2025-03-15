#include "usermanager.h"

UserManager::UserManager()
{
    std::ifstream ifs(USERDATAPATH,std::ios::in);

    //文件不存在
    if(!ifs.is_open())
    {
        qDebug()<<QString("文件不存在").arg(USERDATAPATH);

        this->userNum = 0;
        this->userArray = nullptr;
        this->fileIsEmpty = true;

        ifs.close();
        return;
    }

    //文件存在但为空
    char ch;
    ifs>>ch;
    if(ifs.eof())
    {
        qDebug()<<QString("文件为空").arg(USERDATAPATH);

        this->userNum = 0;
        this->userArray = nullptr;
        this->fileIsEmpty = true;

        ifs.close();
        return;
    }

    //文件存在，记录数据
    this->userNum = getUserNum();
    this->userArray = new User * [this->userNum];
    this->initUser();

    ifs.close();
}

void UserManager::addUser(QString userName, QString pwd)
{
    //用户人数加1
    this->userNum++;

    //开辟新空间
    User ** newSpace = new User* [this->userNum];

    //拷贝旧数据
    for(int i=0;i<this->userNum - 1;i++)
    {
        newSpace[i] = this->userArray[i];
    }

    //添加新数据
    User * newUser = new User;
    newUser->userName = userName;
    newUser->password = pwd;

    newSpace[this->userNum - 1] = newUser;

    //释放原有空间
    delete[] this->userArray;
    //更改新空间指向
    this->userArray = newSpace;


    //保存到文件
    this->save();
    this->fileIsEmpty = false;
}

void UserManager::save()
{
    std::ofstream ofs(USERDATAPATH,std::ios::out);

    for(int i=0;i<this->userNum;i++)
    {

        ofs<<this->userArray[i]->userName.toStdString()<<" "
            <<this->userArray[i]->password.toStdString()<<std::endl;

        QMap<int, int>::iterator it;
        for (it = this->userArray[i]->gameRecord.begin(); it != this->userArray[i]->gameRecord.end(); it++)
        {
            ofs<<it.key()<<" "<<it.value()<<std::endl;
        }
    }

    ofs.close();
}

int UserManager::getUserNum()
{
    //记录用户人数
    int cnt = 0;

    std::ifstream ifs(USERDATAPATH,std::ios::in);

    std::string name;
    std::string pwd;

    while(ifs>>name && ifs>>pwd)
    {
        //读取用户记录
        for(int i=0;i<SELECTBTNNUMBER;i++)
        {
            int level;
            int record;

            ifs>>level;
            ifs>>record;
        }

        cnt++;
    }

    ifs.close();

    return cnt;
}

void UserManager::initUser()
{
    std::ifstream ifs(USERDATAPATH,std::ios::in);

    std::string name;
    std::string pwd;

    int index = 0;  //用于添加用户

    //读取用户名和密码
    while(ifs>>name && ifs>>pwd)
    {
        User * user = new User;
        user->userName = QString::fromStdString(name);
        user->password = QString::fromStdString(pwd);

        //读取用户记录
        for(int i=0;i<SELECTBTNNUMBER;i++)
        {
            int level;
            int record;

            ifs>>level;
            ifs>>record;

            user->gameRecord[level] = record;
        }

        this->userArray[index++] = user;
    }

    ifs.close();
}

void UserManager::userSort(int level)
{
    QString name;
    int record;

    //将指定关卡的数据放入容器
    for(int i=0;i<userNum;i++)
    {
        name = this->userArray[i]->userName;
        record = this->userArray[i]->gameRecord[level];

        this->rankList.push_back(std::pair<QString,int>(name,record));
    }

    //对容器进行排序
    std::sort(rankList.begin(), rankList.end(), [](const std::pair<QString, int>& a, const std::pair<QString, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first; // 如果 record 相同，按名字排序
        }
        return a.second < b.second; // 按 int 排序
    });
}

void UserManager::findUser()
{

}

int UserManager::verifyUserInfo(QString name, QString password)
{
    //验证用户信息

    //返回值 1：不存在用户 2：密码错误 3：登录成功
    for(int i=0;i<this->userNum;i++)
    {
        QString tempName = this->userArray[i]->userName;
        QString tempPwd = this->userArray[i]->password;
        if(tempName == name && tempPwd ==password)
        {
            return 3;  //成功找到
        }
        else if(tempName == name && tempPwd != password)
        {
            return 2;  //密码错误
        }
    }
    return 1;
}

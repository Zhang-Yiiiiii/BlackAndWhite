#include "antgame.h"

AntGame::AntGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent)
    : AbstractGameScene{gameLevel, userName, usermanager, parent}
{

}

//保存自建地图
void AntGame::saveGame(gameMode buildWay, int step, int x, int y, int direction)
{
    //判断是否可解 并且保存地图
    if(buildWay == startingPointMode) //起点建图
    {
        if(!startingPointMaping(this->m_gameArray, QPoint(x, y), direction, step)) //不可解
        {
            QMessageBox::about(this, "提醒", "该设计游戏无解！请重新设计");
            return;
        }
    }
    else  //终点建图
    {
        if(!destinationMaping(this->m_gameArray, QPoint(x, y), direction, step)) //不可解
        {
            QMessageBox::about(this, "提醒", "该设计游戏无解！请重新设计");
            return;
        }
    }

    //进行返回操作
    emit changeBack();
}

bool AntGame::startingPointMaping(std::vector<std::vector<bool> >& gameArray, QPoint pos, int bugDir, int step)
{
    bool tempArray[20][20];
    int tempStep = step;

    //起点
    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            tempArray[i][j] = gameArray[i][j];
        }
    }

    //模拟前进过程
    // 1 向前走一步 step--
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转
    // 3 改变前一个格子颜色
    while(tempStep--)
    {
        //改变前一格颜色
        tempArray[x][y] = !tempArray[x][y];

        //进行前进
        if(bugDir == 0)
        {
            y--;
        }
        else if(bugDir == 1)
        {
            x--;
        }
        else if(bugDir == 2)
        {
            y++;
        }
        else if(bugDir == 3)
        {
            x++;
        }

        //改变方向
        if(tempArray[x][y])  //白色
        {
            bugDir++; //右转方向加一
            bugDir %= 4;
        }
        else
        {
            bugDir += 3; //左转方向加三
            bugDir %= 4;
        }

        //跃出格子
        if(x >= 20 || x < 0 || y < 0 || y >= 20)
        {
            return false;
        }
    }

    //将结果传给data
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            this->m_data->m_gameArray[m_gameLevel][i][j] = tempArray[i][j];
            this->m_data->m_ansArray[m_gameLevel][i][j] = gameArray[i][j];
        }
    }

    this->m_data->m_bugDir[m_gameLevel] = bugDir;
    this->m_data->m_bugPos[m_gameLevel] = QPoint(x, y);
    this->m_data->m_stepArray[m_gameLevel] = step;

    return true;
}

bool AntGame::destinationMaping(std::vector<std::vector<bool> >& gameArray, QPoint pos, int bugDir, int step)
{
    bool tempArray[20][20];
    int tempStep = step;
    int dir = bugDir;

    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            tempArray[i][j] = gameArray[i][j];
        }
    }

    //模拟后退过程
    // 1 将最后一个格子改变颜色 方便统一操作
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转 （黑色意味着之前是白色，当时右转，现在左转回来）
    // 3 后退一步，前一步格子颜色改变 step--
    tempArray[x][y] = !tempArray[x][y]; //改变最后一格颜色

    while(tempStep--)
    {
        if(tempArray[x][y])  //白色
        {
            bugDir++; //右转方向加一
            bugDir %= 4;
        }
        else
        {
            bugDir--;  //左转方向减一

            if(bugDir < 0)
            {
                bugDir += 4;
            }
        }

        //改变前一格颜色
        tempArray[x][y] = !tempArray[x][y];

        //进行后退
        if(bugDir == 0)
        {
            y++;
        }
        else if(bugDir == 1)
        {
            x++;
        }
        else if(bugDir == 2)
        {
            y--;
        }
        else if(bugDir == 3)
        {
            x--;
        }

        //跃出格子
        if(x >= 20 || x < 0 || y < 0 || y >= 20)
        {
            return false;
        }
    }

    //将第一格的颜色改变
    tempArray[x][y] = !tempArray[x][y];

    //将答案保存
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            this->m_data->m_gameArray[m_gameLevel][i][j] = gameArray[i][j];
            this->m_data->m_ansArray[m_gameLevel][i][j] = tempArray[i][j];
        }
    }

    this->m_data->m_bugDir[m_gameLevel] = dir;
    this->m_data->m_bugPos[m_gameLevel] = pos;
    this->m_data->m_stepArray[m_gameLevel] = step;

    return true;
}

int AntGame::getTotalTime()
{
    //计算总时间
    int totalTime = m_passingTime;
    totalTime += m_penaltyTime;

    return totalTime;
}

void AntGame::showBug()
{
    QPushButton * bugBtn = new QPushButton(this);

    //虫子所在坐标轴与窗口长宽不对应
    bugBtn->move(BOARDPOSX + m_bugPos.y() * (GRIDSIZE + 1), BOARDPOSY + m_bugPos.x() * (GRIDSIZE + 1)); //移动bug

    //加载图片
    QString pixStr = QString(BUGPATH).arg(m_bugDir);
    m_bugPix.load(pixStr);
    bugBtn->setFixedSize(m_bugPix.size());
    bugBtn->setIconSize(m_bugPix.size());
    bugBtn->setIcon(QIcon(m_bugPix));
    bugBtn->setStyleSheet("QPushButton{border:0px}");  //设置不规则图形

    //设置属性
    bugBtn->setAttribute(Qt::WA_TransparentForMouseEvents);  //设置可以透明点击
    bugBtn->setEnabled(false);  //设置不能点击
}

bool AntGame::isWin()
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(m_ansArray[i][j] != m_gameArray[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

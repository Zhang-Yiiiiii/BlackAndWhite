#include "lightoutgame.h"

LightOutGame::LightOutGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, gameMode mode)
    : AbstractGameScene{gameLevel, userName, usermanager, parent, mode}
{
    setboardSize(); //获取棋盘大小

    initVector();   //初始化棋盘vector
    initGameInfo();    //初始化游戏信息

    setAnimationType(Animator::SlideFromTop);   //设置动画效果是滑动
    showBoard(false);    //显示棋盘
    setAnimation(); //设置动画

    usermanager->userSort(gameLevel);    //对本关的用户进行排序

    initTimer();    //初始化定时器
    showTimeLabel();    //显示时间

    showPushButton();   //显示提交、返回、重置按钮

    initClickRecord();  //初始化点击数组
}

void LightOutGame::saveGame()
{
    while(!isSolvable())  //不可解
    {
        QMessageBox::about(this, "提醒", "该设计无解，请重新设计");
        return;
    }

    emit changeBack();
}

void LightOutGame::initGameInfo()
{
    //初始化游戏信息对象
    m_data = new Data;

    //初始化信息
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
        }
    }
}

//计算总时间
int LightOutGame::getTotalTime()
{
    int totalTime = m_passingTime;
    return totalTime;
}

//判断是否胜利
bool LightOutGame::isWin()
{
    for (int i = 0; i < m_boardRow; i++)
    {
        for( int j = 0; j < m_boardCol; j++)
        {
            if(!m_gameArray[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

//翻转格子
void LightOutGame::flipCells(const int x, const int y)
{
    //翻转自身
    m_board[x][y]->changeFlag();
    m_gameArray[x][y] = !m_gameArray[x][y];

    //翻转左边
    if(y - 1 >= 0)
    {
        m_board[x][y - 1]->changeFlag();
        m_gameArray[x][y - 1] = !m_gameArray[x][y - 1];
    }

    //翻转上面
    if(x - 1 >= 0)
    {
        m_board[x - 1][y]->changeFlag();
        m_gameArray[x - 1][y] = !m_gameArray[x - 1][y];
    }

    //翻转右边
    if(y + 1 < m_boardCol)
    {
        m_board[x][y + 1]->changeFlag();
        m_gameArray[x][y + 1] = !m_gameArray[x][y + 1];
    }

    //翻转下面
    if(x + 1 < m_boardRow)
    {
        m_board[x + 1][y]->changeFlag();
        m_gameArray[x + 1][y] = !m_gameArray[x + 1][y];
    }
}

//判断是否有解
bool LightOutGame::isSolvable()
{
    int solution = 0;   //第一行的按法

    //复制原数组
    std::vector<std::vector<bool>> gameArray = m_gameArray;

    //用二进制枚举第一行的解法
    for(; solution < (1 << m_boardCol); solution++)
    {
        //答案数组
        std::vector<std::vector<bool >> ans(m_boardRow, std::vector<bool>(m_boardCol, 0));

        for(int i = 0; i < m_boardCol; i++)
        {
            if((solution >> i) & 1) //说明第m_boardCol - i - 1个需要按下
            {
                flipCells(0, m_boardCol - i - 1);
                ans[0][m_boardCol - i - 1] = 1;
            }
        }

        //依此按第一行下面的开关
        for(int i = 0; i < m_boardRow - 1; i++)
        {
            for(int j = 0; j < m_boardCol; j++)
            {
                if(!m_gameArray[i][j]) //说明其为黑色
                {
                    flipCells(i + 1, j);
                    ans[i + 1][j] = 1;
                }
            }
        }

        //验证最后一行是否是全白
        bool flag = true;

        for(int i = 0; i < m_boardCol; i++)
        {
            if(!m_gameArray[m_boardRow - 1][i]) //有黑色的格子
            {
                flag = false;
                break;
            }
        }

        if(flag)
        {
            //保存数据
            saveSolvableInfo(gameArray, ans);
            return true;    //最后一行全为白 有解
        }
        m_gameArray.assign(gameArray.begin(), gameArray.end());
    }

    return false;    //没有找到解
}

//保存数据
void LightOutGame::saveSolvableInfo(std::vector<std::vector<bool> >& gameArray, std::vector<std::vector<bool> >& ans)
{
    //将结果传给data
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            this->m_data->m_gameArray[m_gameLevel][i][j] = gameArray[i][j];
            this->m_data->m_ansArray[m_gameLevel][i][j] = ans[i][j];
        }
    }
}

//初始化点击数组
void LightOutGame::initClickRecord()
{
    m_clickRecord.resize(m_boardRow, std::vector<bool>(m_boardCol, 0));
}

//显示提示
void LightOutGame::generateTipArray()
{
    m_tipsArray.resize(m_boardRow, std::vector<bool>(m_boardCol, 0));

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_tipsArray[i][j] = m_data->m_ansArray[m_gameLevel][i][j];

            if(m_clickRecord[i][j]) //该方块被翻转过
            {
                m_tipsArray[i][j] = !m_tipsArray[i][j];
            }
        }
    }
}

//监听格子被点击
void LightOutGame::onBoardClicked(int x, int y)
{
    //监听格子被点击时翻转
    if(m_gameMode == playMode || m_gameMode == onlineMode) //翻转自身和周围
    {
        flipCells(x, y);    //翻转

        m_clickRecord[x][y] = !m_clickRecord[x][y]; //记录点击位置
    }
    else if(m_gameMode == lightBuildMode)   //只翻转自身
    {
        m_board[x][y]->changeFlag();
        m_gameArray[x][y] = !m_gameArray[x][y];
    }
}

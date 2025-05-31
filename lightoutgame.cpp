#include "lightoutgame.h"
#include <bitset>

//----------------------------------构造析构--------------------------------------------

LightOutGame::LightOutGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, BuildWay mode)
    : AbstractGameScene{gameLevel, userName, usermanager, parent, mode}
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    // initGameInfo();    //初始化游戏信息

    //setAnimationType(Animator::SlideFromTop);   //设置动画效果是滑动

    // showBoard(false);    //显示棋盘

    // setAnimation(); //设置动画

    usermanager->userSort(gameLevel);    //对本关的用户进行排序

    // initTimer();    //初始化定时器

    // showTimeLabel();    //显示时间

    // showPushButton();   //显示提交、返回、重置按钮

    showDifficultyLabel(judgeDiff());     //显示难度

    //点击答案按钮罚时
    connect(showAnswearAction, &QAction::triggered, this, [this]()
    {
        m_penaltyTime += m_boardRow * m_boardCol * 30; //每个格子罚时半分钟
    });

    initClickRecord();  //初始化点击记录数组

    connect(this, &LightOutGame::resetGameSignal, this, &LightOutGame::initClickRecord); //清空点击数组
}

//----------------------------------公有方法--------------------------------------------

//初始化点击数组
void LightOutGame::initClickRecord()
{
    m_clickRecord.clear();
    m_clickRecord.resize(m_boardRow, std::vector<bool>(m_boardCol, 0));
}

//翻转格子
void LightOutGame::flipCells(const int x, const int y, bool isShowAnimation)
{
    auto flip = [this, isShowAnimation](int x, int y)
    {
        m_board[x][y]->changeFlag(isShowAnimation);
        m_gameArray[x][y] = !m_gameArray[x][y];
    };

    //翻转自身
    flip(x, y);

    //翻转左边
    if(y - 1 >= 0)
    {
        flip(x, y - 1);
    }

    //翻转上面
    if(x - 1 >= 0)
    {
        flip(x - 1, y);
    }

    //翻转右边
    if(y + 1 < m_boardCol)
    {
        flip(x, y + 1);
    }

    //翻转下面
    if(x + 1 < m_boardRow)
    {
        flip(x + 1, y);
    }
}

//判断是否有解
bool LightOutGame::isSolvable()
{
    const int N = m_boardRow * m_boardRow; //总数

    std::vector<int> ans(N);
    std::vector<std::vector<bool >> gameArray = m_gameArray;

    bool flag = false;

    const int maxSolveGameLevel = 42;

    if(m_gameLevel < maxSolveGameLevel)    //42关之前使用枚举求解 这样有最小步数
    {
        flag = partialEnumeration(gameArray, ans);
    }

    else    //其他的使用线代求解 时间复杂度低
    {
        flag = linearAlgebra_solve(gameArray, ans);
    }

    //判断
    if(!flag)
    {
        return false;
    }

    //计算答案
    std::vector<std::vector<bool>> finalAns(m_boardRow, std::vector<bool>(m_boardCol, 0));

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(ans[i * m_boardRow + j])
            {
                finalAns[i][j] = 1;
            }
        }
    }

    saveSolvableInfo(gameArray, finalAns);  //保存数据

    return true;
}

//解线性方程来求解 Ax = b
// b: 原矩阵  x: 所求答案  n: 阶数
bool LightOutGame::linearAlgebra_solve(const std::vector<std::vector<bool >> & b, std::vector<int>& x)
{
    int n = b.size();
    int N = n * n;  //总个数
    std::vector<row> A; //影响矩阵
    A.assign(N, row(0));

    //计算位置
    auto index = [](int n, int r, int c)
    {
        return n * r + c;
    };

    // 遍历每个格子，构建点击该格子时影响哪些格子
    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < n; ++c)
        {
            int pos = index(n, r, c);
            A[pos][pos] = 1; // 自己

            if (r > 0)
            {
                A[pos][index(n, r - 1, c)] = 1;    // 上
            }

            if (r < n - 1)
            {
                A[pos][index(n, r + 1, c)] = 1;    // 下
            }

            if (c > 0)
            {
                A[pos][index(n, r, c - 1)] = 1;    // 左
            }

            if (c < n - 1)
            {
                A[pos][index(n, r, c + 1)] = 1;    // 右
            }

            A[pos][N] = b[r][c] ^ 1; // 增广列   对b异或实现目标是开灯1
        }
    }

    int row = 0;

    for (int col = 0; col < N; ++col)
    {
        // 找主元
        int pivot = -1;

        for (int i = row; i < N; ++i)
        {
            if (A[i][col])
            {
                pivot = i;
                break;
            }
        }

        if (pivot == -1)
        {
            continue;
        }

        swap(A[pivot], A[row]);

        // 消除其他行的当前列
        for (int i = 0; i < N; ++i)
        {
            if (i != row && A[i][col])
            {
                A[i] ^= A[row]; //只有 0 和 1 直接使用异或
            }
        }

        ++row;
    }

    // 判断是否有解
    for (int i = row; i < N; ++i)
    {
        if (A[i][N])
        {
            return false;    // 无解：0 = 1
        }
    }

    // 回代：取自由变量为 0
    x.assign(N, 0);

    for (int i = N - 1; i >= 0; --i)
    {
        int pos = -1;

        for (int j = 0; j < N; ++j)
        {
            if (A[i][j])
            {
                pos = j;
                break;
            }
        }

        if (pos == -1)
        {
            continue;    // 全 0 行
        }

        x[pos] = A[i][N];

        for (int j = pos + 1; j < N; ++j)
        {
            if (A[i][j])
            {
                x[pos] ^= x[j];
            }
        }
    }

    return true;
}

//部分枚举法求解
bool LightOutGame::partialEnumeration(const std::vector<std::vector<bool> >& gameArray, std::vector<int>& x)
{
    int n = m_boardCol;

    int solution = 0;   //第一行的按法
    int minSteps = INT_MAX;    //每种可行解的按下次数
    int minSolution = 0;

    std::vector<std::vector<bool >> finalAns(m_boardRow, std::vector<bool>(m_boardCol, 0)); //最终的答案数组

    //计算位置
    auto index = [](int n, int r, int c)
    {
        return n * r + c;
    };

    //用二进制枚举第一行的解法
    for(; solution < (1 << m_boardCol); solution++)
    {
        int cnt = 0;

        for(int i = 0; i < m_boardCol; i++)
        {
            if((solution >> i) & 1) //说明第m_boardCol - i - 1个需要按下
            {
                cnt++;
                flipCells(0, m_boardCol - i - 1);
            }
        }

        //依此按第一行下面的开关
        for(int i = 0; i < m_boardRow - 1; i++)
        {
            for(int j = 0; j < m_boardCol; j++)
            {
                if(!m_gameArray[i][j]) //说明其为黑色
                {
                    cnt++;
                    flipCells(i + 1, j);
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

        if(flag)    //有解
        {
            //记录最小解
            if(cnt < minSteps)
            {
                minSteps = cnt;
                minSolution = solution;
            }
        }

        m_gameArray.assign(gameArray.begin(), gameArray.end());
    }

    //得到最终解
    if(minSteps != INT_MAX)
    {
        qDebug() << "minSteps" << minSteps;

        for(int j = 0; j < m_boardCol; j++)
        {
            if((minSolution >> j) & 1) //说明第m_boardCol - j - 1个需要按下
            {
                flipCells(0, m_boardCol - j - 1);
                x[index(n, 0, m_boardCol - j - 1)] = 1;
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
                    x[index(n, i + 1, j)] = 1;
                }
            }
        }

        return true;
    }
    return false;    //没有找到解
}

// //计算总时间
// int LightOutGame::getTotalTime() const
// {
// return m_passingTime;
// }

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

//保存游戏
void LightOutGame::saveGame()
{
    while(!isSolvable())  //不可解
    {
        QMessageBox::about(this, "提醒", "该设计无解，请重新设计");
        resetGame();
        return;
    }

    emit changeBack();
}

//评分
ScoreLevel LightOutGame::Scoring()
{
    ScoreLevel score;
    int time = getTotalTime();

    if(time <= qPow(2, m_boardRow))
    {
        score = ScoreLevel::S;
    }
    else if(time <= 2 * qPow(2, m_boardRow))
    {
        score = ScoreLevel::A;
    }
    else if(time <= 3 * qPow(3, m_boardRow))
    {
        score = ScoreLevel::B;
    }
    else if(time <= 4 * qPow(4, m_boardRow))
    {
        score = ScoreLevel::C;
    }
    else
    {
        score = ScoreLevel::D;
    }

    return score;
}

//判断是否胜利
bool LightOutGame::isWin() const
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

//判定难度
QString LightOutGame::judgeDiff()
{
    //根据棋盘大小判定
    QString level = "";

    if(m_boardRow <= 4)
    {
        level = "萌新";
    }
    else if(m_boardRow <= 7)
    {
        level = "标准";
    }
    else if(m_boardRow <= 10)
    {
        level = "困难";
    }
    else
    {
        level = "地狱";
    }

    return level;
}

//计算经验
unsigned int LightOutGame::calculateExp()
{
    int mul = static_cast<int>(5 - Scoring());  //倍数
    return mul * m_boardRow * m_boardRow;
}

//----------------------------------公共槽--------------------------------------------

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

//随机生成地图按钮被点击
void LightOutGame::onRandomBtnClicked()
{
    //记录当前模式
    BuildWay mode = m_gameMode;
    m_gameMode = playMode;  //实现熄灯游戏的周围翻转

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(std::rand() % 2) //对该格子随机进行翻转
            {
                flipCells(i, j, false);
            }
        }
    }

    //还原模式
    m_gameMode = mode;
}

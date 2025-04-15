#include "gamescene.h"

#include "config.h"
#include <iostream>
#include <sstream>
#include <fstream>

GameScene::GameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent)
    : QMainWindow{parent}, m_gameLevel{gameLevel}, m_userName(userName), m_usermanager(usermanager)
{
    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH, BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));

    //设置菜单栏
    QMenuBar * menubar = menuBar();
    menubar->setParent(this);
    menubar->setStyleSheet("font: 700 12pt \"Microsoft YaHei UI\"; background-color: rgba(217, 217, 217, 150); color: rgb(66, 66, 66);");

    QMenu * startMenu = menubar->addMenu("开始");
    QMenu * gameMenu = menubar->addMenu("游戏");
    QMenu * toolMenu = menubar->addMenu("工具");

    QAction * quitAction = startMenu->addAction("退出游戏");

    QAction * instructionAction = gameMenu->addAction("说明");
    QAction * rankAction = gameMenu->addAction("排行榜");

    //连接排行榜按钮
    connect(rankAction, &QAction::triggered, this, &GameScene::showRankList);

    //显示游戏说明
    connect(instructionAction, &QAction::triggered, this, [ = ]()
    {
        this->showRule();
    });

    //退出游戏
    connect(quitAction, &QAction::triggered, [ = ]()
    {
        exit(0);
    });

    initGameInfo();    //初始化游戏信息
    usermanager->userSort(gameLevel);    //对本关的用户进行排序
    initTimer();    //初始化定时器
    showBoard();    //显示棋盘
    showBug();  //显示虫子
    showStepLabel();    //显示步数label
    showTimeLabel();    //显示时间label
    showPushButton();   //显示提交、返回、重置按钮
}

//显示游戏说明
void GameScene::showRule()
{
    std::ifstream ifs(RULEPATH);

    // 打开文件
    if (!ifs.is_open())
    {
        QMessageBox::about(this, "通知", QString("无法打开文件").arg(RULEPATH));
        return;
    }

    // 使用 std::stringstream 读取整个文件内容
    std::stringstream buffer;
    buffer << ifs.rdbuf(); // 将文件内容读取到 stringstream 中

    //关闭文件
    ifs.close();

    // 将 stringstream 的内容转换为 QString
    QString fileContent = QString::fromStdString(buffer.str());

    QMessageBox::about(this, "说明", fileContent);
}

//显示排行榜
void GameScene::showRankList()
{
    const QPoint pos(20, 70);

    if(!m_rankWindow)
    {
        m_rankWindow = new RankList(this->m_usermanager->m_rankList, this);
    }

    m_rankWindow->move(pos);
    m_rankWindow->show();
}

//显示棋盘的函数
void GameScene::showBoard()
{
    //棋盘位置
    int x = BOARDPOSX;
    int y = BOARDPOSY;

    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            m_board[i][j] = new GridButton(m_gameArray[i][j], this);

            m_board[i][j]->posx = i;
            m_board[i][j]->posy = j;

            //监听格子被点击时翻转
            connect(m_board[i][j], &QPushButton::clicked, [ = ]()
            {
                m_board[i][j]->changeFlag();
                m_gameArray[i][j] = !m_gameArray[i][j];
            });

            m_board[i][j]->move(x, y);
            x += GRIDSIZE + 1;
        }

        x = BOARDPOSX;
        y += GRIDSIZE + 1;
    }
}

//显示虫子
void GameScene::showBug()
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

//重写绘图事件
void GameScene::paintEvent(QPaintEvent*)
{
    //实例化画家
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    //加载背景
    QPixmap pix;
    pix.load(BACKGROUDPATH);
    painter.drawPixmap(0, 0, pix);
}

//判断是否胜利
bool GameScene::isWin()
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

//重置棋盘
void GameScene::resetGame()
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(m_gameArray[i][j] != m_data->m_gameArray[m_gameLevel][i][j])  //有些格子被点击了
            {
                m_board[i][j]->changeFlag();
                m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
            }
        }
    }
}

//判断是否有解  已知起点信息
bool GameScene::startingPointMaping(bool gameArray[][20], QPoint pos, int bugDir, int step)
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

//判断是否有解  已知终点
bool GameScene::destinationMaping(bool gameArray[][20], QPoint pos, int bugDir, int step) //棋盘 虫子位置 方向 步数
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

//保存自建地图
void GameScene::saveGame(gameMode buildWay, int step, int x, int y, int direction)
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

//保存总用时
int GameScene::saveTotalTime()
{
    //计算总时间
    int totalTime = getTotalTime();

    //更新时间
    m_usermanager->updateTotalTime(this->m_userName, totalTime, this->m_gameLevel);

    return totalTime;
}

//获取用户当前所用总时间
int GameScene::getTotalTime()
{
    //计算总时间
    int totalTime = m_passingTime;
    totalTime += m_penaltyTime;

    return totalTime;
}

//初始化步数label
void GameScene::showStepLabel()
{
    //步数说明
    QLabel * stepLabel = new QLabel(this);
    stepLabel->setText(QString::number(this->m_gameStep));
    stepLabel->move(40, 40);
    QFont stepLabelFont;
    stepLabelFont.setBold(true);
    stepLabelFont.setPointSize(12);
    stepLabel->setFont(stepLabelFont);
}

//初始化时间label
void GameScene::showTimeLabel()
{
    //显示用时的label
    m_timeLabel = new QLabel(this);
    m_timeLabel->setFixedWidth(200);
    m_timeLabel->setText("所用时间：00:00:00");
    m_timeLabel->move(150, 400);
    m_timeLabel->setStyleSheet("QLabel { font-family: '华文新魏'; "
                               "font-weight: bold; "
                               "font-size: 20px; color: #333333; "
                               "background-color: #ffffff; "
                               "border: 2px solid #ffffff; "
                               "border-radius: 10px; }");

    m_timeLabel->setAlignment(Qt::AlignCenter);

    //罚时label
    m_timePenaltyLabel = new QLabel(this);
    m_timePenaltyLabel->setFixedWidth(200);
    m_timePenaltyLabel->setText("所罚时间：00:00:00");
    m_timePenaltyLabel->move(150, 400 + m_timeLabel->height() + 10);
    m_timePenaltyLabel->setStyleSheet("QLabel { font-family: '华文新魏'; "
                                      "font-weight: bold; "
                                      "font-size: 20px; color: #333333; "
                                      "background-color: #ffffff; "
                                      "border: 2px solid #ffffff; "
                                      "border-radius: 10px; }");

    m_timePenaltyLabel->setAlignment(Qt::AlignCenter);
}

//初始化定时器
void GameScene::initTimer()
{
    //初始化定时器
    m_elapsedTimer = new QElapsedTimer;
    m_elapsedTimer->start();

    m_showTimer = new QTimer(this);
    m_showTimer->start(100);

    //监听showTimer对用户通关时间进行更新
    connect(m_showTimer, &QTimer::timeout, this, &GameScene::updateTime);
}

//初始化游戏信息
void GameScene::initGameInfo()
{
    //初始化游戏信息对象
    m_data = new Data;

    //初始化信息
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
            m_ansArray[i][j] = m_data->m_ansArray[m_gameLevel][i][j];
        }
    }

    //初始化虫子所在位置、方向 750 400 游戏步数
    m_bugPos.setX(m_data->m_bugPos[m_gameLevel].x());
    m_bugPos.setY(m_data->m_bugPos[m_gameLevel].y());
    m_bugDir = m_data->m_bugDir[m_gameLevel];
    m_gameStep = m_data->m_stepArray[m_gameLevel];
}

//初始化按钮
void GameScene::showPushButton()
{
    //设置返回按钮
    backBtn = new QPushButton(this);
    backBtn->setText("返 回");
    backBtn->setFont(QFont("华文新魏", 15));
    backBtn->setFixedSize(120, 50);
    backBtn->move(BACKGROUDWIDTH - backBtn->width(), BACKGROUDHEIGHT - backBtn->height());
    connect(backBtn, &QPushButton::clicked, [ = ]()
    {
        emit changeBack();
    });

    //设置提交按钮
    submitBtn = new QPushButton(this);
    submitBtn->setText("提 交");
    submitBtn->setFont(QFont("华文新魏", 15));
    submitBtn->setFixedSize(120, 50);
    submitBtn->move(BACKGROUDWIDTH - submitBtn->width(), BACKGROUDHEIGHT - 2 * submitBtn->height());
    connect(submitBtn, &QPushButton::clicked, this, [ = ]()
    {
        //判断是否胜利
        if(isWin())
        {
            if(m_gameMode == playMode)
            {
                QMessageBox::about(this, "通过", "恭喜你成功通过此关");
                saveTotalTime();
                emit changeBack();  //进行返回
            }
            else if (m_gameMode == onlineMode)
            {
                const int totalTime = getTotalTime();
                saveTotalTime();
                m_showTimer->stop();
                emit gameOver(totalTime);
            }
        }
        else
        {
            QMessageBox::about(this, "失败", "答案错误，罚时30秒");
            this->resetGame(); //重置棋盘
            this->m_penaltyTime += 30; //罚时增加
        }
    });

    //重置按钮
    resetBtn = new QPushButton(this);
    resetBtn->setText("重 置");
    resetBtn->setFont(QFont("华文新魏", 15));
    resetBtn->setFixedSize(120, 50);
    resetBtn->move(BACKGROUDWIDTH - resetBtn->width(), BACKGROUDHEIGHT - 3 * resetBtn->height());
    connect(resetBtn, &QPushButton::clicked, this, [ = ]()
    {
        int ret = QMessageBox::question(this, "问题", "是否确定重置？");

        if(ret == QMessageBox::Yes)
        {
            this->resetGame(); //进行重置
            m_penaltyTime += 30;
        }
    });
}

//更新显示时间
void GameScene::updateTime()
{
    int secs = m_elapsedTimer->elapsed() / 1000;
    m_passingTime = secs;

    int mins = secs / 60;
    int hours = mins / 60;
    secs %= 60;
    mins %= 60;
    m_timeLabel->setText(QString::asprintf("所用时间：%02d:%02d:%02d", hours, mins, secs));

    secs = m_penaltyTime % 60;
    mins = m_penaltyTime / 60 % 60;
    hours = m_penaltyTime / 3600;
    m_timePenaltyLabel->setText(QString::asprintf("所罚时间：%02d:%02d:%02d", hours, mins, secs));
}

GameScene::~GameScene()
{
    //删除数据对象
    delete m_data;
    m_data = nullptr;

    delete m_elapsedTimer;
    m_elapsedTimer = nullptr;

    m_usermanager = nullptr;  //不要释放 因为是主页面传入的参数

    //释放board
    for (int i = 0; i < BOARDSIDELENGTH; i++)
    {
        for (int j = 0; j < BOARDSIDELENGTH; j++)
        {
            delete m_board[i][j];
            m_board[i][j] = nullptr;
        }
    }
}

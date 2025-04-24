#include "abstractgamescene.h"

#include "config.h"
#include <iostream>
#include <sstream>
#include <fstream>

AbstractGameScene::AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, gameMode mode)
    : QMainWindow(parent), m_gameMode(mode), m_gameLevel{gameLevel}, m_userName(userName), m_usermanager(usermanager)
{
    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH, BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));

    //设置菜单栏
    QMenuBar * menubar = menuBar();
    menubar->setParent(this);
    menubar->setStyleSheet("font: 700 12pt \"Microsoft YaHei UI\"; background-color: rgba(217, 217, 217, 150); color: rgb(66, 66, 66);");

    //设置菜单
    QMenu * startMenu = menubar->addMenu("开始");
    QMenu * gameMenu = menubar->addMenu("游戏");
    QMenu * toolMenu = menubar->addMenu("工具");

    //设置菜单项
    QAction * quitAction = startMenu->addAction("退出游戏");

    QAction * instructionAction = gameMenu->addAction("说明");
    QAction * rankAction = gameMenu->addAction("排行榜");

    //退出游戏
    connect(quitAction, &QAction::triggered, [ = ]()
    {
        exit(0);
    });

    //显示游戏说明
    connect(instructionAction, &QAction::triggered, this, [ = ]()
    {
        this->showRule();
    });

    //连接排行榜按钮
    connect(rankAction, &QAction::triggered, this, &AbstractGameScene::showRankList);
}

//显示游戏说明
void AbstractGameScene::showRule()
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

//重写绘图事件
void AbstractGameScene::paintEvent(QPaintEvent*)
{
    //实例化画家
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    //加载背景
    QPixmap pix;
    pix.load(BACKGROUDPATH);
    painter.drawPixmap(0, 0, pix);
}

//设置棋盘尺寸
void AbstractGameScene::setboardSize()
{
    //兰顿蚂蚁游戏关卡数 37
    if (m_gameLevel > 0 && m_gameLevel <= ANTGAMENUMBER)
    {
        m_boardRow = m_boardCol = 20;   //棋盘大小为 20*20
    }
    else
    {
        //lightGame 的棋盘从4*4开始递增
        m_boardRow = m_boardCol = m_gameLevel - ANTGAMENUMBER + 3;
    }
}

//初始化棋盘大小
void AbstractGameScene::initVector()
{
    m_board.resize(m_boardRow);
    m_gameArray.resize(m_boardRow);
    m_ansArray.resize(m_boardRow);

    for(int i = 0; i < m_boardRow; i++)
    {
        m_board[i].resize(m_boardCol);
        m_gameArray[i].resize(m_boardCol);
        m_ansArray[i].resize(m_boardCol);
    }
}

//显示棋盘的函数
void AbstractGameScene::showBoard()
{
    //棋盘位置
    int x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
    int y = (BACKGROUDHEIGHT - m_boardCol * GRIDSIZE) / 2;

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_board[i][j] = new GridButton(m_gameArray[i][j], this);

            m_board[i][j]->posx = i;
            m_board[i][j]->posy = j;

            //监听格子被点击时翻转
            connect(m_board[i][j], &GridButton::beClicked, this, &AbstractGameScene::onBoardClicked);

            m_board[i][j]->move(x, y);
            x += GRIDSIZE + 1;
        }

        x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
        y += GRIDSIZE + 1;
    }
}

//重置棋盘
void AbstractGameScene::resetGame()
{
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(m_gameArray[i][j] != m_data->m_gameArray[m_gameLevel][i][j])  //有些格子被点击了
            {
                m_board[i][j]->changeFlag();
                m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
            }
        }
    }
}

//显示排行榜
void AbstractGameScene::showRankList()
{
    const QPoint pos(20, 70);   //排行榜显示的位置

    if(!m_rankWindow)
    {
        m_rankWindow = new RankList(this->m_usermanager->m_rankList, this);
    }

    m_rankWindow->move(pos);
    m_rankWindow->show();
}

//提交按钮被点击的槽函数
void AbstractGameScene::onSubmitBtnClicked()
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
        QMessageBox::about(this, "失败", "答案错误");
        this->resetGame(); //重置棋盘
    }
}

void AbstractGameScene::onResetBtnClicked()
{
    int ret = QMessageBox::question(this, "问题", "是否确定重置？");

    if(ret == QMessageBox::Yes)
    {
        this->resetGame(); //进行重置
    }
}

void AbstractGameScene::onBoardClicked(int x, int y)
{
    m_board[x][y]->changeFlag();
    m_gameArray[x][y] = !m_gameArray[x][y];
}

//初始化定时器
void AbstractGameScene::initTimer()
{
    //初始化定时器
    m_elapsedTimer = new QElapsedTimer;
    m_elapsedTimer->start();

    m_showTimer = new QTimer(this);
    m_showTimer->start(100);

    //监听showTimer对用户通关时间进行更新
    connect(m_showTimer, &QTimer::timeout, this, &AbstractGameScene::updateTime);
}

//保存总用时
int AbstractGameScene::saveTotalTime()
{
    //计算总时间
    int totalTime = getTotalTime();

    //更新时间
    m_usermanager->updateTotalTime(this->m_userName, totalTime, this->m_gameLevel);

    return totalTime;
}

//初始化时间label
void AbstractGameScene::showTimeLabel()
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
}

//初始化游戏信息
void AbstractGameScene::initGameInfo()
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

//设置提交按钮
void AbstractGameScene::setSubmitBtn()
{
    submitBtn = new QPushButton(this);
    submitBtn->setText("提 交");
    submitBtn->setFont(QFont("华文新魏", 15));
    submitBtn->setFixedSize(120, 50);
    submitBtn->move(BACKGROUDWIDTH - submitBtn->width(), BACKGROUDHEIGHT - 2 * submitBtn->height());

    connect(submitBtn, &QPushButton::clicked, this, &AbstractGameScene::onSubmitBtnClicked);
}

//设置返回按钮
void AbstractGameScene::setBackBtn()
{
    backBtn = new QPushButton(this);
    backBtn->setText("返 回");
    backBtn->setFont(QFont("华文新魏", 15));
    backBtn->setFixedSize(120, 50);
    backBtn->move(BACKGROUDWIDTH - backBtn->width(), BACKGROUDHEIGHT - backBtn->height());

    connect(backBtn, &QPushButton::clicked, this, [ = ]()
    {
        emit changeBack();
    });
}

//设置重置按钮
void AbstractGameScene::setResetBtn()
{
    resetBtn = new QPushButton(this);
    resetBtn->setText("重 置");
    resetBtn->setFont(QFont("华文新魏", 15));
    resetBtn->setFixedSize(120, 50);
    resetBtn->move(BACKGROUDWIDTH - resetBtn->width(), BACKGROUDHEIGHT - 3 * resetBtn->height());

    connect(resetBtn, &QPushButton::clicked, this, &AbstractGameScene::onResetBtnClicked);
}

//初始化按钮
void AbstractGameScene::showPushButton()
{
    setBackBtn();
    setSubmitBtn();
    setResetBtn();
}

//更新显示时间
void AbstractGameScene::updateTime()
{
    //获取秒数
    int secs = m_elapsedTimer->elapsed() / 1000;
    m_passingTime = secs;

    //转换成时分
    int mins = secs / 60;
    int hours = mins / 60;
    secs %= 60;
    mins %= 60;
    m_timeLabel->setText(QString::asprintf("所用时间：%02d:%02d:%02d", hours, mins, secs));
}

AbstractGameScene::~AbstractGameScene()
{
    //删除数据对象
    delete m_data;
    m_data = nullptr;

    delete m_elapsedTimer;
    m_elapsedTimer = nullptr;

    m_usermanager = nullptr;  //不要释放 因为是主页面传入的参数
}

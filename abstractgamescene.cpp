#include "abstractgamescene.h"
#include "config.h"

AbstractGameScene::AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, gameMode mode)
    : BaseWindow(parent), m_gameMode(mode), m_gameLevel{gameLevel}, m_userName(userName), m_usermanager(usermanager)
{
    QAction * rankAction = m_gameMenu->addAction("排行榜");

    QAction* tipAction = m_toolMenu->addAction("显示提示");     //显示提示
    QAction* closeTipAction = m_toolMenu->addAction("关闭提示");   //关闭提示
    connect(tipAction, &QAction::triggered, this, &AbstractGameScene::onShowTips);
    connect(closeTipAction, &QAction::triggered, this, &AbstractGameScene::clearTipsButton);

    //连接排行榜按钮
    connect(rankAction, &QAction::triggered, this, &AbstractGameScene::showRankList);

    //显示关卡数
    QString level = QString("%1").arg(m_gameLevel, 2, 10, QChar('0'));

    QString digit1 = QString(level[0]);
    QString digit2 = QString(level[1]);

    QString pixStr1 = QString(NUMBERPATH).arg(digit1);
    QString pixStr2 = QString(NUMBERPATH).arg(digit2);

    QPixmap pix1(pixStr1);
    QPixmap pix2(pixStr2);

    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);

    label1->setFixedSize(50, 50);
    label2->setFixedSize(50, 50);

    label1->setPixmap(pix1);
    label2->setPixmap(pix2);

    label1->move(1200, 300);
    label2->move(1250, 300);
    label1->show();
    label2->show();
}

//设置动画类型
void AbstractGameScene::setAnimationType(Animator::AnimationType type)
{
    m_animationType = type;
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
    m_board.clear();
    m_gameArray.clear();
    m_ansArray.clear();

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
void AbstractGameScene::showBoard(bool isVisible)
{
    //棋盘位置
    int x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
    int y = (BACKGROUDHEIGHT - m_boardCol * GRIDSIZE) / 2;

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_board[i][j] = new GridButton(m_gameArray[i][j], this);
            m_board[i][j]->setVisible(isVisible);
            m_board[i][j]->m_posx = i;
            m_board[i][j]->m_posy = j;

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
        m_rankWindow = new RankList(m_usermanager->m_rankList, this);
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
            QMessageBox::about(this, "通过", "恭喜成功通过此关");
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

//随机生成地图
void AbstractGameScene::onRandomBtnClicked()
{
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(std::rand() % 2) //对该格子进行翻转
            {
                if(m_board[i][j])
                {
                    onBoardClicked(i, j);
                }
            }
        }
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
    m_elapsedTimer.start();

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
    m_timeLabel->setText("所用时间：00:00:00");
    m_timeLabel->move(150, 400);
    setLabelStyle(m_timeLabel);
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
        m_isInternalclose = true;   //确定是内部返回的 而不是关闭窗口
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

//设置随机按钮
void AbstractGameScene::setRandomBtn()
{
    randomBtn = new QPushButton(this);
    randomBtn->setText("随机生成");
    randomBtn->setFont(QFont("华文新魏", 15));
    randomBtn->setFixedSize(120, 50);
    randomBtn->move(BACKGROUDWIDTH - submitBtn->width(), BACKGROUDHEIGHT - 2 * submitBtn->height());

    randomBtn->hide();  //开始设置不可见

    connect(randomBtn, &QPushButton::clicked, this, &AbstractGameScene::onRandomBtnClicked);
}

//初始化按钮
void AbstractGameScene::showPushButton()
{
    setBackBtn();
    setSubmitBtn();
    setResetBtn();
    setRandomBtn();
}

#include <QPointer>
//设置动画
void AbstractGameScene::setAnimation(int delay)
{
    int startTime = 0;

    for(auto btns : m_board)
    {
        for(auto btn : btns)
        {
            QPointer<QPushButton> safeBtn = btn;    //用安全指针判断控件是否存在
            QTimer::singleShot(startTime, [ = ]()
            {
                if(safeBtn)
                {
                    auto ani = Animator::createAnimator(safeBtn, m_animationType);
                    safeBtn->setVisible(true);
                    ani ->start();
                }
            });

            startTime += delay;
        }
    }
}

//提示功能
void AbstractGameScene::onShowTips()
{
    clearTipsButton();  //清空之前的按钮

    if(m_gameMode != playMode)
    {
        QMessageBox::about(this, "提示", "只有单人模式支持提示功能");
        return;
    }

    // QMessageBox::about(this, "提示", "提示功能将会增加两分钟的时长");
    // m_passingTime += 120;

    //生成提示数组
    generateTipArray();

    //棋盘位置
    int x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
    int y = (BACKGROUDHEIGHT - m_boardCol * GRIDSIZE) / 2;

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(m_tipsArray[i][j])
            {
                int posx = x + j * (GRIDSIZE + 1);
                int posy = y + i * (GRIDSIZE + 1);

                QPushButton * tipBtn = new QPushButton(this);
                m_tipsButtons.push_back(tipBtn);    //放入提示按钮数组

                QPixmap pix = QPixmap(TIPPATH);
                tipBtn->setFixedSize(35, 35);
                tipBtn->setIconSize(pix.size());
                tipBtn->setIcon(QIcon(pix));
                tipBtn->setStyleSheet("QPushButton{border:0px}");  //设置不规则图形

                tipBtn->move(posx, posy);
                tipBtn->show();
                connect(tipBtn, &QPushButton::clicked, tipBtn, [ = ]()
                {
                    m_board[i][j]->click();
                    tipBtn->hide();
                });
            }
        }
    }
}

//清空提示按钮
void AbstractGameScene::clearTipsButton()
{
    for(auto btn : m_tipsButtons)
    {
        if(btn)
        {
            btn->deleteLater();    //删除按钮
            btn = nullptr;
        }
    }

    m_tipsButtons.clear();
}

//设置label统一格式
void AbstractGameScene::setLabelStyle(QLabel *label)
{
    label->setFixedWidth(200);
    label->setStyleSheet("QLabel { font-family: '华文新魏'; "
                         "font-weight: bold; "
                         "font-size: 20px; color: #333333; "
                         "background-color: #ffffff; "
                         "border: 2px solid #ffffff; "
                         "border-radius: 10px; }");
    label->setAlignment(Qt::AlignCenter);
}

//更新显示时间
void AbstractGameScene::updateTime()
{
    //获取秒数
    int secs = m_elapsedTimer.elapsed() / 1000;
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
    if(m_data)
    {
        delete m_data;
        m_data = nullptr;
    }

    m_usermanager = nullptr;  //不要释放 因为是主页面传入的参数
}

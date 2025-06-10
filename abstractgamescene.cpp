#include "abstractgamescene.h"
#include "chatdialog.h"
#include "mypushbutton.h"
#include "fancybaseplate.h"
#include "config.h"

#include <QPointer>

//----------------------------------构造和析构--------------------------------------------
AbstractGameScene::AbstractGameScene(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, BuildWay mode)
    : BaseWindow(parent), m_userName(userName), m_gameLevel{gameLevel}, m_usermanager(usermanager), m_gameMode(mode)
{
    //排行榜
    QAction * rankAction = m_gameMenu->addAction("排行榜");
    rankAction->setIcon(QIcon(RANKLISHICONPAHT));
    connect(rankAction, &QAction::triggered, this, &AbstractGameScene::onRankActionClicked);

    //显示答案
    showAnswearAction = m_toolMenu->addAction("显示答案");
    showAnswearAction->setIcon(QIcon(SHOWTIPICONPATH));
    connect(showAnswearAction, &QAction::triggered, this, &AbstractGameScene::onShowTips);

    //关闭答案
    QAction* closeTipAction = m_toolMenu->addAction("关闭答案");
    closeTipAction->setIcon(QIcon(CLOSETIPICONPATH));
    connect(closeTipAction, &QAction::triggered, this, &AbstractGameScene::clearTipsButton);

    initGameInfo();    //初始化游戏信息

    setAnimationType(rand() % 2 ? Animator::SlideFromTop : Animator::FadeIn); //设置动画效果

    //棋盘位置
    int x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
    int y = (BACKGROUDHEIGHT - m_boardCol * GRIDSIZE) / 2;
    boardPos.setX(x);
    boardPos.setY(y);

    // 创建 8x8 棋盘，位置在 (50, 50)
    FancyBasePlate* basePlate = new FancyBasePlate(
        this,   // 父组件
        QPoint(x, y), // 位置
        m_boardRow,              // 行数
        m_boardCol               // 列数
    );

    basePlate->show();

    showBoard(false);    //显示棋盘

    setAnimation(); //设置动画

    showTimeLabel();    //显示时间label

    QPointer<AbstractGameScene> selfPtr;
    selfPtr = this; // 保存弱引用
    QTimer::singleShot(m_boardRow * 100, [ = ]()    //延迟出动画时间
    {
        if (!selfPtr)
        {
            return;    // 检查对象是否存活
        }

        initTimer();
    });

    showPushButton();   //显示提交、返回、重置按钮

    m_menubar->raise(); //让菜单栏置顶 不然有时 点击没有反应

    //ai
    m_ai = new ChatDialog(this);

    QAction * aiAction = m_menubar->addAction("ai帮助");
    connect(aiAction, &QAction::triggered, m_ai, &QDialog::show);
    connect(m_ai, &ChatDialog::applyAidInfo, this, [ = ]()
    {
        m_ai->onGetAidInfo(getInfo());
    });
}

AbstractGameScene::~AbstractGameScene()
{
    //删除数据对象
    if(m_data)
    {
        delete m_data;
        m_data = nullptr;
    }
}

//----------------------------------公有方法--------------------------------------------

//隐藏提交按钮
AbstractGameScene* AbstractGameScene::hideSubmitBtn()
{
    if(submitBtn)
    {
        submitBtn->hide();
    }

    return this;
}

//显示随机按钮
AbstractGameScene* AbstractGameScene::showRandomBtn()
{
    if(randomBtn)
    {
        randomBtn->show();
    }

    return this;
}

//设置内部关闭标志
AbstractGameScene* AbstractGameScene::setInternalClose(bool flag)
{
    m_isInternalclose = flag;
    return this;
}

//设置动画类型
void AbstractGameScene::setAnimationType(Animator::AnimationType type)
{
    m_animationType = type;
}

//保存可解数据
void AbstractGameScene::saveSolvableInfo(const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans)
{
    //传入数据有误
    if((int)gameArray.size() != m_boardRow || (int)gameArray[0].size() != m_boardCol)
    {
        return;
    }

    if((int)ans.size() != m_boardRow || (int)ans[0].size() != m_boardCol)
    {
        return;
    }

    m_data->saveData(m_gameLevel, gameArray, ans);
}

void AbstractGameScene::saveSolvableInfo(const std::vector<std::vector<bool> >& gameArray, const std::vector<std::vector<bool> >& ans, int steps, int dir, QPoint pos)
{
    //传入数据有误
    if((int)gameArray.size() != m_boardRow || (int)gameArray[0].size() != m_boardCol)
    {
        return;
    }

    if((int)ans.size() != m_boardRow || (int)ans[0].size() != m_boardCol)
    {
        return;
    }

    //将答案保存
    m_data->saveData(m_gameLevel, gameArray, ans, steps, dir, pos);
}

//设置按钮是否可按
void AbstractGameScene::setBtnEnabled(bool enable)
{
    //重置按钮
    resetBtn->setEnabled(enable);

    //提交按钮
    submitBtn->setEnabled(enable);

    //随机按钮
    randomBtn->setEnabled(enable);

    //返回按钮
    backBtn->setEnabled(enable);
}

//返回按钮是否可按
void AbstractGameScene::setBackBtnEnabled(bool enabled)
{
    backBtn->setEnabled(enabled);
}

QString AbstractGameScene::getInfo()
{
    QString result;
    QTextStream stream(&result);

    // 添加数组维度信息
    if (!m_gameArray.empty())
    {
        stream << "Array Size: " << m_boardRow
               << "x" << m_boardCol << "\n";
    }

    stream << "\n";

    // 转换数组内容
    for (int row = 0; row < m_boardRow; ++row)
    {

        // 数组数据
        for (int col = 0; col < m_boardCol; ++col)
        {
            stream << QString("  %1").arg(m_gameArray[row][col] ? " 1 " : " 0 ");
        }

        stream << "\n";
    }

    return result;
}

//----------------------------------保护方法--------------------------------------------

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

//初始化游戏信息
void AbstractGameScene::initGameInfo()
{
    //初始化游戏信息对象
    if(!m_data)
    {
        m_data = new Data;
    }

    setboardSize(); //获取棋盘大小

    initVector();   //初始化棋盘vector

    //初始化信息
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
            m_ansArray[i][j] = m_data->m_ansArray[m_gameLevel][i][j];
        }
    }
}

//显示棋盘的函数
void AbstractGameScene::showBoard(bool isVisible)
{
    //棋盘位置
    int x = boardPos.x();
    int y = boardPos.y();

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            m_board[i][j] = new GridButton(m_gameArray[i][j], this);
            m_board[i][j]->setVisible(isVisible);
            m_board[i][j]->setPos(i, j);

            //监听格子被点击时翻转
            connect(m_board[i][j], &GridButton::beClicked, this, &AbstractGameScene::onBoardClicked);

            m_board[i][j]->move(x, y);
            x += GRIDSIZE + 1;
        }

        x = boardPos.x();
        y += GRIDSIZE + 1;
    }
}

//初始化时间label
void AbstractGameScene::showTimeLabel()
{
    //显示用时的label
    m_timeLabel = new QLabel(this);
    m_timeLabel->setText("所用时间：00:00:00");
    m_timeLabel->move(150, 400);
    setLabelStyle(m_timeLabel);

    //罚时label
    if(!m_timePenaltyLabel)
    {
        m_timePenaltyLabel = new QLabel(this);
    }

    m_timePenaltyLabel = new QLabel(this);
    setLabelStyle(m_timePenaltyLabel);
    m_timePenaltyLabel->setText("所罚时间：00:00:00");
    m_timePenaltyLabel->move(150, 400 + m_timeLabel->height() + 10);
}

//显示难度等级label
void AbstractGameScene::showDifficultyLabel(QString difficulty)
{
    m_difficultyLabel = new QLabel(this);
    setLabelStyle(m_difficultyLabel);
    QString str = QString("难度等级：%1").arg(difficulty);
    m_difficultyLabel->setText(str);
    m_difficultyLabel->move(150, 400 + 3 * m_timeLabel->height() );
}

//初始化定时器
void AbstractGameScene::initTimer()
{
    //初始化定时器
    m_elapsedTimer.start();

    m_showTimer = new QTimer(this);
    m_showTimer->start(100);

    //监听showTimer对用户通关时间进行更新
    connect(m_showTimer, &QTimer::timeout, this, &AbstractGameScene::onUpdateTime);
}

//保存总用时
int AbstractGameScene::saveTotalTime()
{
    //计算总时间
    int totalTime = getTotalTime();

    //更新时间
    m_usermanager->updateUserTime(m_userName, totalTime, m_gameLevel);

    return totalTime;
}

//获取总时间
int AbstractGameScene::getTotalTime() const
{
    //计算总时间
    int totalTime = m_passingTime;
    totalTime += m_penaltyTime;

    return totalTime;
}

//设置提交按钮
void AbstractGameScene::setSubmitBtn()
{
    submitBtn = MyPushButton::createButton(MyPushButton::commonButton, "提 交", this);
    submitBtn->move(BACKGROUDWIDTH - submitBtn->width(), BACKGROUDHEIGHT - 2 * submitBtn->height());

    connect(submitBtn, &QPushButton::clicked, this, &AbstractGameScene::onSubmitBtnClicked);
}

//设置返回按钮
void AbstractGameScene::setBackBtn()
{
    backBtn = MyPushButton::createButton(MyPushButton::commonButton, "返 回", this);
    backBtn->move(BACKGROUDWIDTH - backBtn->width(), BACKGROUDHEIGHT - backBtn->height());

    connect(backBtn, &QPushButton::clicked, this, [ = ]()
    {
        // m_isInternalclose = true;   //确定是内部返回的 而不是关闭窗口
        emit changeBack();
    });
}

//设置重置按钮
void AbstractGameScene::setResetBtn()
{
    resetBtn = MyPushButton::createButton(MyPushButton::commonButton, "重 置", this);
    resetBtn->move(BACKGROUDWIDTH - resetBtn->width(), BACKGROUDHEIGHT - 3 * resetBtn->height());

    connect(resetBtn, &QPushButton::clicked, this, &AbstractGameScene::onResetBtnClicked);
}

//设置随机按钮
void AbstractGameScene::setRandomBtn()
{
    randomBtn = MyPushButton::createButton(MyPushButton::commonButton, "随机生成", this);
    randomBtn->move(BACKGROUDWIDTH - submitBtn->width(), BACKGROUDHEIGHT - 2 * submitBtn->height());

    randomBtn->hide();  //开始设置不可见

    connect(randomBtn, &QPushButton::clicked, this, &AbstractGameScene::onRandomBtnClicked);
}

//重置棋盘
void AbstractGameScene::resetGame()
{
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            //分开判断 因为在求解过程中可能导致两者装态不一致
            if(m_gameArray[i][j] != m_data->m_gameArray[m_gameLevel][i][j])
            {
                m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
            }

            if(m_board[i][j]->getFlag() != m_data->m_gameArray[m_gameLevel][i][j])
            {
                m_board[i][j]->changeFlag();
            }
        }
    }

    emit resetGameSignal();
}

//初始化按钮
void AbstractGameScene::showPushButton()
{
    setBackBtn();
    setSubmitBtn();
    setResetBtn();
    setRandomBtn();
}

//设置动画
void AbstractGameScene::setAnimation(int delay)
{
    int startTime = 400;    //动画起始时间

    for(auto& btns : m_board)
    {
        for(auto& btn : btns)
        {
            QPointer<QPushButton> safeBtn = btn;    //用安全指针判断控件是否存在

            if(safeBtn)
            {
                auto ani = Animator::createAnimator(safeBtn, m_animationType, 800);
                ani->onFinished([ = ]()
                {
                    ani->deleteLater();
                });

                QTimer::singleShot(startTime, ani, [ani]()
                {

                    ani ->start();
                });
            }

            startTime += delay;
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

//重写显示事件
void AbstractGameScene::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    emit sceneShow();
}

//重写移动事件
void AbstractGameScene::moveEvent(QMoveEvent *event)
{
    m_ai->move(QPoint(frameGeometry().right() + 3, frameGeometry().top()));
    BaseWindow::moveEvent(event);
}

//重写关闭事件
void AbstractGameScene::closeEvent(QCloseEvent *event)
{
    if(m_isInternalclose)
    {
        event->accept();
    }

    else
    {
        QCoreApplication::quit();
    }
}

//棋盘被点击
void AbstractGameScene::onBoardClicked(int x, int y)
{
    m_board[x][y]->changeFlag();
    m_gameArray[x][y] = !m_gameArray[x][y];
}

//提交按钮被点击的槽函数
void AbstractGameScene::onSubmitBtnClicked()
{
    //判断是否胜利
    if(isWin())
    {
        if(m_gameMode == playMode)
        {
            //计算评分
            ScoreLevel score;
            score = Scoring();

            //保存时间
            m_showTimer->stop();    //停止计时
            saveTotalTime();

            //对话框
            QString str = QString("恭喜成功通过此关 %1 级").arg(ScoreMap[score]);
            QMessageBox::about(this, "通过", str);

            //计算经验
            m_usermanager->addExp(m_usermanager->findUser(m_userName), calculateExp());
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
        this->m_penaltyTime += 30; //罚时增加
    }
}

//重置按钮被点击
void AbstractGameScene::onResetBtnClicked()
{
    int ret = QMessageBox::question(this, "问题", "是否确定重置？重置罚时30秒");

    if(ret == QMessageBox::Yes)
    {
        this->resetGame(); //进行重置
        m_penaltyTime += 30;
    }
}

//随机生成地图
void AbstractGameScene::onRandomBtnClicked()
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
                if(m_board[i][j])
                {
                    onBoardClicked(i, j);
                }
            }
        }
    }

    //还原模式
    m_gameMode = mode;
}

//更新显示时间
void AbstractGameScene::onUpdateTime()
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

    secs = m_penaltyTime % 60;
    mins = m_penaltyTime / 60 % 60;
    hours = m_penaltyTime / 3600;
    m_timePenaltyLabel->setText(QString::asprintf("所罚时间：%02d:%02d:%02d", hours, mins, secs));
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
    int x = boardPos.x();
    int y = boardPos.y();

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(m_tipsArray[i][j])
            {
                int posx = x + j * (GRIDSIZE + 1);
                int posy = y + i * (GRIDSIZE + 1);

                QPushButton * tipBtn = MyPushButton::createButton(MyPushButton::tipButton, "", this);
                m_tipsButtons.push_back(tipBtn);    //放入提示按钮数组

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

//显示排行榜
void AbstractGameScene::onRankActionClicked()
{
    const QPoint pos(20, 70);   //排行榜显示的位置

    if(!m_rankWindow)
    {
        m_rankWindow = new RankList(m_usermanager->m_rankList, this);
    }

    m_rankWindow->move(pos);
    m_rankWindow->show();
}

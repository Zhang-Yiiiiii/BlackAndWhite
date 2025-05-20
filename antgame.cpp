#include "antgame.h"
#include <QColorDialog>
#include <QToolTip>

constexpr int BOARD_SIZE = 20;  //棋盘的行数和列数

bool AntGame::m_isShowPath = false;

//----------------------------------构造析构--------------------------------------------

AntGame::AntGame(int gameLevel, QString userName, UserManager * usermanager, QWidget *parent, BuildWay mode)
    : AbstractGameScene{gameLevel, userName, usermanager, parent, mode}
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    initBugInfo();   //初始化bug信息

    setAnimationType(rand() % 2 ? Animator::FadeIn : Animator::SlideFromTop); //设置动画

    showBug();      //显示bug

    usermanager->userSort(gameLevel);    //对本关的用户进行排序

    showStepLabel();    //显示步数label

    //点击答案按钮罚时
    connect(showAnswearAction, &QAction::triggered, this, [this]()
    {
        m_penaltyTime += m_gameStep * 60; //每一步罚时一分钟
    });

    //逐步提示按钮
    MyPushButton* showHintBtn = MyPushButton::createButton(MyPushButton::commonButton, "逐步提示", this);
    showHintBtn->move(BACKGROUDWIDTH - showHintBtn->width(), BACKGROUDHEIGHT - 4 * showHintBtn->height());
    connect(showHintBtn, &MyPushButton::clicked, this, &AntGame::onShowHintBtnClicked);

    //工具菜单
    QMenu* toolBar = qobject_cast<QMenu*>(m_menubar->children().at(3));
    toolBar->addSeparator();
    QAction* currentStepsAction = toolBar->addAction("显示当前步数");     //显示当前步数
    connect(currentStepsAction, &QAction::triggered, this, &AntGame::onShowCurrentSteps);

    //路径显示
    QMenu* pathMenu = toolBar->addMenu("路径");
    QAction* showPathAction = pathMenu->addAction("显示路径");
    QAction* closePathAction = pathMenu->addAction("关闭路径");
    connect(showPathAction, &QAction::triggered, this, &AntGame::onShowPathClicked);
    connect(closePathAction, &QAction::triggered, this, &AntGame::onHidePathClicked);

    QAction* chooseColorAction = pathMenu->addAction("路径颜色");
    connect(chooseColorAction, &QAction::triggered, this, &AntGame::onChooseColorClicked);

    recordPath();   //记录路径

    initOverlay();  //初始化覆盖层

}

AntGame::~AntGame()
{
}

//----------------------------------公有方法--------------------------------------------

//保存自建地图
void AntGame::saveGame(BuildWay buildWay, int step, int x, int y, int direction)
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

void AntGame::paintEvent(QPaintEvent *event)
{
    BaseWindow::paintEvent(event);
    QPainter painter(this);

    if(m_isShowPath)
    {
        generatePath();
    }

}

//----------------------------------私有方法--------------------------------------------

// //初始化游戏信息
// void AntGame::initGameInfo()
// {
//     //初始化游戏信息对象
// if(!m_data)
// {
// m_data = new Data;
// }

// setboardSize(); //获取棋盘大小

// initVector();   //初始化棋盘vector

//     //初始化信息
// for(int i = 0; i < m_boardRow; i++)
// {
// for(int j = 0; j < m_boardCol; j++)
// {
// m_gameArray[i][j] = m_data->m_gameArray[m_gameLevel][i][j];
// m_ansArray[i][j] = m_data->m_ansArray[m_gameLevel][i][j];
// }
// }

//     //初始化虫子所在位置、方向 750 400 游戏步数
// m_bugPos.setX(m_data->m_bugPos[m_gameLevel].x());
// m_bugPos.setY(m_data->m_bugPos[m_gameLevel].y());
// m_bugDir = m_data->m_bugDir[m_gameLevel];
// m_gameStep = m_data->m_stepArray[m_gameLevel];
// }

//初始化bug
void AntGame::initBugInfo()
{
    //初始化虫子所在位置、方向 750 400 游戏步数
    m_bugPos.setX(m_data->m_bugPos[m_gameLevel].x());
    m_bugPos.setY(m_data->m_bugPos[m_gameLevel].y());
    m_bugDir = m_data->m_bugDir[m_gameLevel];
    m_gameStep = m_data->m_stepArray[m_gameLevel];
}

//显示bug
void AntGame::showBug()
{
    QPushButton * bugBtn = new QPushButton(this);

    //移动bug
    //虫子所在坐标轴与窗口长宽不对应
    bugBtn->move(BOARDPOSX + m_bugPos.y() * (GRIDSIZE + 1), BOARDPOSY + m_bugPos.x() * (GRIDSIZE + 1));

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

// //显示时间
// void AntGame::showTimeLabel()
// {
//     //显示用时的label
// if(!m_timeLabel)
// {
// m_timeLabel = new QLabel(this);
// }

// setLabelStyle(m_timeLabel);
// m_timeLabel->setText("所用时间：00:00:00");
// m_timeLabel->move(150, 400);

//     //罚时label
// if(!m_timePenaltyLabel)
// {
// m_timePenaltyLabel = new QLabel(this);
// }

// setLabelStyle(m_timePenaltyLabel);
// m_timePenaltyLabel->setText("所罚时间：00:00:00");
// m_timePenaltyLabel->move(150, 400 + m_timeLabel->height() + 10);
// }

// //获取总时间
// int AntGame::getTotalTime() const
// {
//     //计算总时间
// int totalTime = m_passingTime;
// totalTime += m_penaltyTime;

// return totalTime;
// }

//初始化步数label
void AntGame::showStepLabel()
{
    //步数说明
    QLabel * stepLabel = new QLabel(this);
    setLabelStyle(stepLabel);

    stepLabel->setText("本关步数: " + QString::number(this->m_gameStep));
    stepLabel->move(150, 360);
}

//更新当前步数
void AntGame::updateCurrentSteps(unsigned int steps)
{
    m_currentSteps = steps;

    if(m_currentStepsLabel)
    {
        m_currentStepsLabel->setText(QString("当前步数：%1").arg(m_currentSteps));
    }
}

//判断是否胜利
bool AntGame::isWin() const
{
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(m_ansArray[i][j] != m_gameArray[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

//起点建图
bool AntGame::startingPointMaping(std::vector<std::vector<bool> >& gameArray, QPoint pos, int bugDir, int step)
{
    std::vector<std::vector<bool>> tempArray(BOARD_SIZE, std::vector<bool>(BOARD_SIZE));
    int tempStep = step;

    //起点
    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            tempArray[i][j] = gameArray[i][j];
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

        //跃出格子
        if(x >= BOARD_SIZE || x < 0 || y < 0 || y >= BOARD_SIZE)
        {
            return false;
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
    }

    //将结果传给data
    saveSolvableInfo(tempArray, gameArray, step, bugDir, QPoint(x, y));
    return true;
}

//终点建图
bool AntGame::destinationMaping(std::vector<std::vector<bool> >& gameArray, QPoint pos, int bugDir, int step)
{
    m_hintArray.clear();

    std::vector<std::vector<bool>> tempArray(BOARD_SIZE, std::vector<bool>(BOARD_SIZE));
    int tempStep = step;
    int dir = bugDir;

    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0; i < BOARD_SIZE; i++)
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            tempArray[i][j] = gameArray[i][j];
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
            bugDir++; //右转  方向加一
            bugDir %= 4;
        }
        else
        {
            bugDir--;  //左转  方向减一

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
        if(x >= BOARD_SIZE || x < 0 || y < 0 || y >= BOARD_SIZE)
        {
            return false;
        }

        //将数据保存至逐步提示数组
        m_hintArray.append(QPoint(x, y));
    }

    //将第一格的颜色改变
    tempArray[x][y] = !tempArray[x][y];

    //将结果传给data
    saveSolvableInfo(gameArray, tempArray, step, dir, pos);

    return true;
}

//生成提示数组
void AntGame::generateTipArray()
{
    m_tipsArray.resize(m_boardRow, std::vector<bool>(m_boardCol, 0));

    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            //和答案不对的地方需要按下
            m_tipsArray[i][j] = m_data->m_ansArray[m_gameLevel][i][j] != m_gameArray[i][j];
        }
    }
}

//记录路径
void AntGame::recordPath()
{
    for(auto &btns : m_board)
    {
        for(auto & btn : btns)
        {
            connect(btn, &GridButton::beClicked, this, [this, btn](int posx, int posy)
            {
                //像素坐标
                QPoint pixPos = btn->mapTo(this, btn->rect().center());
                m_path.append(pixPos);

                //判断是否点击的是提示格子
                if(m_isHinting && hintSteps < m_hintArray.size())
                    if(posx != m_hintArray[hintSteps].x() || posy != m_hintArray[hintSteps].y())
                    {
                        m_isHinting = false;
                        hintSteps = 0;
                    }
            });
        }
    }
}

//生成路径数组
void AntGame::generatePath()
{
    if(!m_overlay)
    {
        return;
    }
    else if (m_path.empty() || !m_isShowPath)
    {
        m_overlay->clearPath();
        return;
    }

    // 更新覆盖层显示
    m_overlay->setPath(m_path);
}

//初始化覆盖层
void AntGame::initOverlay()
{
    // 创建覆盖层
    m_overlay = new Overlay(this);
    m_overlay->setGeometry(this->geometry());  // 初始大小匹配父窗口
    m_overlay->raise();         // 提升到最上层
}

//棋盘是否是最初状态
bool AntGame::isBoardInitial()
{
    for(int i = 0; i < m_boardRow; i++)
    {
        for(int j = 0; j < m_boardCol; j++)
        {
            if(m_gameArray[i][j] != m_data->m_gameArray[m_gameLevel][i][j])
            {
                return false;
            }
        }
    }

    return true;

}

//----------------------------------私有槽--------------------------------------------

//提交
void AntGame::onSubmitBtnClicked()
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
        this->onResetBtnClicked(); //重置棋盘
        this->m_penaltyTime += 30; //罚时增加
    }
}

//重置棋盘
void AntGame::onResetBtnClicked()
{
    int ret = QMessageBox::question(this, "问题", "是否确定重置？重置罚时30秒");

    if(ret == QMessageBox::Yes)
    {
        this->resetGame(); //进行重置
        m_penaltyTime += 30;
        updateCurrentSteps(0);
    }

    //清除路径
    m_path.clear();

    //清除答案数组
    clearTipsButton();

    //清楚逐步提示步数
    hintSteps = 0;
}

//棋盘被点击
void AntGame::onBoardClicked(int x, int y)
{
    updateCurrentSteps(++m_currentSteps);
    AbstractGameScene::onBoardClicked(x, y);

    if(hintSteps == m_gameStep) //如果是已经提示到最后一步之后再次点击
    {
        m_isHinting = false;
    }
}

//显示当前步数
void AntGame::onShowCurrentSteps()
{
    if(!m_currentStepsLabel)
    {
        m_currentStepsLabel = new QLabel(this);
    }

    setLabelStyle(m_currentStepsLabel);

    m_currentStepsLabel->setText(QString("当前步数：%1").arg(m_currentSteps));
    m_currentStepsLabel->move(150, 400 + 2 * m_timeLabel->height() + 20);
    m_currentStepsLabel->show();
}

//更新时间
// void AntGame::onUpdateTime()
// {
// int secs = m_elapsedTimer.elapsed() / 1000;
// m_passingTime = secs;

// int mins = secs / 60;
// int hours = mins / 60;
// secs %= 60;
// mins %= 60;
// m_timeLabel->setText(QString::asprintf("所用时间：%02d:%02d:%02d", hours, mins, secs));

// secs = m_penaltyTime % 60;
// mins = m_penaltyTime / 60 % 60;
// hours = m_penaltyTime / 3600;
// m_timePenaltyLabel->setText(QString::asprintf("所罚时间：%02d:%02d:%02d", hours, mins, secs));
// }

//显示路径
void AntGame::onShowPathClicked()
{
    if (!m_isShowPath)
    {
        m_isShowPath = true;
        generatePath(); // 重新生成路径
        m_overlay->update(); // 强制重绘覆盖层
    }
}

//隐藏路径
void AntGame::onHidePathClicked()
{
    if (m_isShowPath)
    {
        m_isShowPath = false;
        m_overlay->clearPath(); // 清除路径数据
        m_overlay->update();
    }
}

//选择路径颜色
void AntGame::onChooseColorClicked()
{
    // 弹出颜色选择对话框
    QColor color = QColorDialog::getColor(
                       Qt::red,                      // 默认颜色
                       this,                        // 父窗口
                       "选择路径颜色",               // 对话框标题
                       QColorDialog::ShowAlphaChannel // 可选：允许选择透明度
                   );

    if (color.isValid())   // 用户点击了"确定"
    {
        // 更新覆盖层颜色
        m_overlay->setPathColor(color);

        // // 可选：将按钮背景色设置为当前颜色
        // QString style = QString(
        // "QPushButton { padding: 8px; background: %1; color: %2; }"
        // ).arg(color.name()).arg(
        // color.lightness() > 128 ? "black" : "white" // 自动调整文字颜色
        // );
        // m_btnChooseColor->setStyleSheet(style);
    }
}

//逐步显示提示
void AntGame::onShowHintBtnClicked()
{
    if(!isBoardInitial() && !m_isHinting)   //棋盘不是最初状态 也不处于提示状态
    {
        QPoint pos = QPoint(this->rect().width() / 2, 500);
        QToolTip::showText(pos, "请先重置棋盘", this, rect(), 500);
        return;
    }
    else if(isBoardInitial() && !m_isHinting)   //棋盘是初始状态 但不是提示状态
    {
        destinationMaping(m_gameArray, m_bugPos, m_bugDir, m_gameStep); //求解步数
        hintSteps = 0;
        m_isHinting = true;
    }

    if(hintSteps == m_gameStep)
    {
        return;
    }

    // else if(hintSteps > m_gameStep) //点击次数大于游戏步数
    // {
    // m_isHinting = false;
    // }

    if(m_hintBtn)
    {
        m_hintBtn->deleteLater();
    }

    m_hintBtn = MyPushButton::createButton(MyPushButton::tipButton, "", this);

    //棋盘位置
    int x = (BACKGROUDWIDTH - m_boardRow * GRIDSIZE) / 2;
    int y = (BACKGROUDHEIGHT - m_boardCol * GRIDSIZE) / 2;

    int row = m_hintArray[hintSteps].x();    //行
    int col = m_hintArray[hintSteps].y();    //列

    m_hintBtn->move(x + (GRIDSIZE + 1)*col, y + (GRIDSIZE + 1)*row);
    m_hintBtn->show();

    connect(m_hintBtn, &QPushButton::clicked, m_hintBtn, [ = ]()
    {
        m_board[row][col]->click();
        m_hintBtn->hide();
        hintSteps++;
    });

    //罚时增加
    m_penaltyTime += 30;

}

#include "mainscene.h"
#include "ui_mainscene.h"

#include <QGraphicsOpacityEffect>
#include "lightoutgame.h"
#include "antgame.h"
#include "animator.h"

MainScene::MainScene(QWidget *parent)
    : BaseWindow(parent)
    , ui(new Ui::MainScene)
{
    //ui->setupUi(this);

    //登录
    QAction* loginAction = m_startMenu->addAction("登录");
    connect(loginAction, &QAction::triggered, this, &MainScene::onUserLogin);

    m_gameMenu->addSeparator();
    //自建地图
    QMenu* antMappingMenu = m_gameMenu->addMenu("兰顿蚂蚁自建地图");

    //起点建图
    QAction* startMapiingAction = antMappingMenu->addAction("起点建图");
    connect(startMapiingAction, &QAction::triggered, this, [this]()
    {
        this->buildAntGame(startingPointMode);
    });

    //终点建图
    QAction* destinationMappingAction = antMappingMenu->addAction("终点建图");
    connect(destinationMappingAction, &QAction::triggered, this, [this]()
    {
        this->buildAntGame(destinationMode);  //终点建图
    });

    //熄灯游戏建图
    QAction* lightMappingActoin = m_gameMenu->addAction("熄灯游戏自建地图");
    connect(lightMappingActoin, &QAction::triggered, this, &MainScene::buildLightGame);

    //进行联机
    QAction* onlineAction = m_toolMenu->addAction("联机");
    connect(onlineAction, &QAction::triggered, this, &MainScene::onOnlineTriggerd);

    //断开联机
    QAction* disconnectAction = m_toolMenu->addAction("断开联机");
    connect(disconnectAction, &QAction::triggered, this, &MainScene::onDisconnectTriggerd);

    //初始化用户管理员
    this->m_usermanager = new UserManager;

    //初始化选关按钮
    initSelectBtn();

    //显示选关六边形
    showSelectBtn();

    //设置动画
    setAnimations();
}

//初始化六边形按钮
void MainScene::initSelectBtn()
{
    for(int i = 0; i < SELECTBTNNUMBER; i++)
    {
        m_selectBtns[i] = new Hexagon(i);

        m_selectBtns[i]->setParent(this);

        //监听六边形被点击的信号  进入游戏场景
        connect(m_selectBtns[i], &Hexagon::beClicked, this, [ = ](int gameLevel)
        {
            onHexagonClicked(gameLevel);
        });
    }
}

//显示选关六边形  监听进入游戏场景
void MainScene::showSelectBtn()
{
    //六边形起始点
    int posx = 950;
    const int length = m_selectBtns[0]->getSideLength();
    int x = 950;
    int y = 200;
    int k = 1;  //每行个数
    int cnt = 4;  //计算每行六边形数量

    //显示上半部分
    for(int i = 0; i < 22; i++)
    {
        m_selectBtns[i]->move(x, y);

        x += length * pow(3, 0.5) + 4;

        if(k % cnt == 0)
        {
            k = 0;
            y += 1.5 * length + 2;
            x = posx - (cnt - 3) * (length * pow(3, 0.5) * 0.5 + 2);
            cnt++;
        }

        k++;
    }

    x += 2 * (length * pow(3, 0.5) * 0.5 + 2);
    cnt = 6;
    k = 1;

    //显示下半部分
    for(int i = 22; i < 37; i++)
    {
        m_selectBtns[i]->move(x, y);

        x += length * pow(3, 0.5) + 4;

        if(k % cnt == 0)
        {
            cnt--;
            k = 0;
            y += 1.5 * length + 2;
            x = posx - (cnt - 4) * (length * pow(3, 0.5) * 0.5 + 2);
        }

        k++;
    }

    //显示lightGame的选关按钮
    posx = 400;
    x = 400;
    y = 250;
    int level = ANTGAMENUMBER;

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            m_selectBtns[level++]->move(x, y);
            x += length * pow(3, 0.5) + 4;
        }

        y += 1.5 * length + 2;
        x = posx - (i + 1) * (length * pow(3, 0.5) * 0.5 + 2);
    }
}

//自建ant地图
void MainScene::buildAntGame(gameMode buildWay)
{
    // 显示对话框
    showBuildDialog(buildWay);
}

//自建light地图
void MainScene::buildLightGame()
{
    int level = QInputDialog::getInt(this, "建立熄灯游戏", "请输入关卡数38-47");
    enterGameScene(level, lightBuildMode);
}

//显示建图对话框
void MainScene::showBuildDialog(gameMode buildWay)
{
    //显示对话框
    m_mydialog = new BuildMapDialog(this);
    m_mydialog->show();

    //从对话框获取信息
    connect(m_mydialog, &BuildMapDialog::getedInfo, this, [ = ]()
    {
        onMapingInfoReceived(buildWay);
    });
}

//进入游戏场景
void MainScene::enterGameScene(int gameLevel, gameMode enterWay, int gameStep, int bugX, int bugY, int bugDirection)
{
    if(gameLevel <= ANTGAMENUMBER) //兰顿蚂蚁模式
    {
        m_gameScene = new AntGame(gameLevel, m_userName, this->m_usermanager, nullptr, enterWay);
    }
    else if(gameLevel <= SELECTBTNNUMBER)   //熄灯游戏模式
    {
        m_gameScene = new LightOutGame(gameLevel, m_userName, this->m_usermanager, nullptr, enterWay);
    }

    //延迟进入
    this->hide();
    m_gameScene->setGeometry(this->geometry());
    m_gameScene->show();

    // 监听返回信号
    connect(m_gameScene, &AbstractGameScene::changeBack, this, &MainScene::onGameSceneChangeBack);

    if (enterWay == playMode) // 游戏模式
    {
        return;
    }
    else if (enterWay == startingPointMode || enterWay == destinationMode || enterWay == lightBuildMode)  // 自建图模式
    {
        // 断开提交按钮
        m_gameScene->submitBtn->setDisabled(true);
        m_gameScene->submitBtn->hide();

        //显示随机生成地图按钮
        m_gameScene->randomBtn->show();

        // 创建保存按钮
        createSaveButton(gameStep, bugX, bugY, bugDirection, enterWay);
    }
    else if(enterWay == onlineMode)    // 联机模式
    {
        setOnlineMode();
    }
}

// 比较结果
void MainScene::compareResults(int ourTime, int rivalTime)
{
    if (ourTime < rivalTime)
    {
        // 我方胜利
        QMessageBox::about(m_gameScene, "提醒", "我方胜利");
    }
    else if (ourTime > rivalTime)
    {
        // 对方胜利
        QMessageBox::about(m_gameScene, "提醒", "对方胜利");
    }
    else
    {
        // 平局
        QMessageBox::about(m_gameScene, "提醒", "平局");
    }

    emit m_gameScene->changeBack();
}

// 处理返回信号
void MainScene::onGameSceneChangeBack()
{
    this->setGeometry(m_gameScene->geometry());
    m_gameScene->close();
    this->show();

    if(m_gameScene)
    {
        delete m_gameScene;
        m_gameScene = nullptr;
    }
}

//处理用户登录
void MainScene::onUserConfirmLogin()
{
    int ret = this->m_usermanager->verifyUserInfo(m_loginWindow->getUserName(), m_loginWindow->getUserPassword());

    //提示信息所在位置
    QPoint pos = m_loginWindow->mapToGlobal(QPoint(m_loginWindow->width() / 2 - 35, m_loginWindow->height() + 100));

    if(ret == 3) //登录成功
    {
        //显示提示信息
        QToolTip::showText(pos, "登录成功", this, this->rect(), 5000);

        //记录用户信息
        this->m_userName = m_loginWindow->getUserName();
        this->m_password = m_loginWindow->getUserPassword();

        this->show();
        m_loginWindow->close();
        delete m_loginWindow;
        m_loginWindow = nullptr;
    }
    else if(ret == 2) //密码错误
    {
        //显示提示信息
        QToolTip::showText(pos, "密码错误", this, this->rect(), 5000);
    }
    else //用户不存在
    {
        //显示提示信息
        QToolTip::showText(pos, "用户不存在", this, this->rect(), 5000);
    }
}

// 创建保存地图按钮
void MainScene::createSaveButton(int gameStep, int bugX, int bugY, int bugDirection, gameMode buildWay)
{
    QPushButton *saveBtn = new QPushButton(m_gameScene);
    saveBtn->setText("保 存");
    saveBtn->setFont(QFont("华文新魏", 15));
    saveBtn->setFixedSize(120, 50);
    saveBtn->move(BACKGROUDWIDTH - saveBtn->width(), BACKGROUDHEIGHT - 4 * saveBtn->height());
    saveBtn->show();

    connect(saveBtn, &QPushButton::clicked, this, [this, gameStep, bugX, bugY, bugDirection, buildWay]()
    {
        handleSaveButtonClicked(buildWay, gameStep, bugX, bugY, bugDirection);
    });
}

// 处理保存地图按钮点击事件
void MainScene::handleSaveButtonClicked(gameMode buildWay, int gameStep, int bugX, int bugY, int bugDirection)
{
    int ret = QMessageBox::question(this, "问题", "确定保存游戏？");

    if (ret == QMessageBox::Yes)
    {
        //兰顿蚂蚁模式
        if(buildWay == startingPointMode || buildWay == destinationMode)
        {
            if(AntGame * antPtr = dynamic_cast<AntGame*>(m_gameScene))
            {
                antPtr->saveGame(buildWay, gameStep, bugX, bugY, bugDirection);
            }
        }
        else if(buildWay == lightBuildMode)
        {
            if(LightOutGame* lightPtr = dynamic_cast<LightOutGame*>(m_gameScene))
            {
                lightPtr->saveGame();
            }
        }
    }
}

//显示登录对话框
void MainScene::showLoginWindow()
{
    if(!m_loginWindow)
    {
        m_loginWindow = new LoginWindow();
    }

    m_loginWindow->setWindowIcon(QIcon(MYICON));
    m_loginWindow->move((this->width() - m_loginWindow->width()) / 2, (this->height() - m_loginWindow->height()) / 2);

    this->hide();
    m_loginWindow->show();

    //关闭对话框时重新显示主页面
    connect(m_loginWindow, &LoginWindow::userClose, this, [ = ]() mutable
    {
        this->show();   //显示游戏界面

        delete m_loginWindow;
        m_loginWindow = nullptr;
    });
}

void MainScene::setOnlineMode()
{
    // 断开已有的连接  不断开连接的话会有bug 程序会崩溃
    disconnect(m_gameScene, &AntGame::gameOver, this, nullptr);
    disconnect(m_onlineWindow, &OnlineWindow::rivalOverGame, this, nullptr);
    disconnect(m_onlineWindow, &OnlineWindow::weWinGame, this, nullptr);
    disconnect(m_onlineWindow, &OnlineWindow::weLoseGame, this, nullptr);

    m_isWeFinished = false; // 我方未完成游戏
    m_isRivalFinished = false; // 对方未完成游戏
    m_ourTotalTime = 0;
    m_rivalTotalTime = 0;

    // 监听我方完成游戏的信号
    connect(m_gameScene, &AntGame::gameOver, this, [ & ](int totalTime)
    {
        m_isWeFinished = true;
        m_ourTotalTime = totalTime;

        // 发送胜利消息给对方
        m_onlineWindow->write("OVER_GAME" + QString::number(totalTime).toUtf8())->flush();

        // 检查对方是否已经完成游戏
        if (m_isRivalFinished)
        {
            compareResults(m_ourTotalTime, m_rivalTotalTime);
        }
        else
        {
            QMessageBox::about(this, "提醒", "等待对方完成游戏");
        }
    });

    // 监听对方完成游戏的信号
    connect(m_onlineWindow, &OnlineWindow::rivalOverGame, this, [ = ](int totalTime)
    {
        m_isRivalFinished = true;
        m_rivalTotalTime = totalTime;

        // 检查我方是否已经完成游戏
        if (m_isWeFinished)
        {
            compareResults(m_ourTotalTime, m_rivalTotalTime);
        }
    });

    // 监听我方赢得游戏
    connect(m_onlineWindow, &OnlineWindow::weWinGame, this, [ = ]()
    {
        QMessageBox::about(m_gameScene, "提醒", "我方胜利");
        emit m_gameScene->changeBack();
    });

    // 监听我方输了游戏
    connect(m_onlineWindow, &OnlineWindow::weLoseGame, this, [ = ]()
    {
        QMessageBox::about(m_gameScene, "提醒", "对方胜利");
        emit m_gameScene->changeBack();
    });
}

void MainScene::setAnimations()
{
    // 创建动画组
    //QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup(this);

    for(auto btn : m_selectBtns)
    {
        // //设置按钮不可见
        // QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(btn);
        // effect->setOpacity(0);
        // btn->setGraphicsEffect(effect);
        // setAnimation(btn, animationGroup);

        Animator * ani = Animator::createAnimator(btn, Animator::SlideFromTop);
        ani->start();

    }

    //animationGroup->start();
}

//设置按钮显示动画
void MainScene::setAnimation(QWidget *widget, QSequentialAnimationGroup *animationGroup)
{
    QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(widget->graphicsEffect());
    QPropertyAnimation *fadeIn = new QPropertyAnimation(effect, "opacity");

    fadeIn->setDuration(50); // 动画时长500ms
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);
    fadeIn->setEasingCurve(QEasingCurve::InQuad); // 平滑曲线

    connect(fadeIn, &QPropertyAnimation::finished, widget, [widget]()  //让动画结束后回到原位置
    {
        widget->move(widget->pos()); // 强制刷新位置
    });

    animationGroup->addAnimation(fadeIn);
}

//用户登录
void MainScene::onUserLogin()
{
    //显示登录对话框
    showLoginWindow();

    //获取登录信息
    connect(m_loginWindow, &LoginWindow::userConfirmed, this, [this]()
    {
        onUserConfirmLogin();
    });

    //用户注册
    connect(m_loginWindow, &LoginWindow::userRegistered, this, [this]()
    {
        onUserConfirmRegister();
    });
}

//选关按钮被点击
void MainScene::onHexagonClicked(int gameLevel)
{
    gameMode mode = playMode;

    if(m_isOnlineMode)
    {
        mode = onlineMode;

        //联机模式 告诉对方也进入
        m_onlineWindow->write("ENTER_GAME" + QString::number(gameLevel).toLatin1())->flush();
    }

    enterGameScene(gameLevel, mode);
}

//从建图对话框中获取信息
void MainScene::onMapingInfoReceived(gameMode buildWay)
{
    int gameLevel, gameStep, bugX, bugY, bugDirection;
    gameLevel = m_mydialog->getNum1();
    gameStep = m_mydialog->getNum2();
    bugX = m_mydialog->getNum3();
    bugY = m_mydialog->getNum4();
    bugDirection = m_mydialog->getNum5();

    //进入游戏场景
    enterGameScene(gameLevel, buildWay, gameStep, bugX, bugY, bugDirection);
}

//用户确定注册
void MainScene::onUserConfirmRegister()
{
    //获取用户输入
    QString name = m_loginWindow->getUserName();
    QString pwd = m_loginWindow->getUserPassword();

    int ret = this->m_usermanager->verifyUserInfo(name, pwd);

    //提示信息所在位置
    QPoint pos = m_loginWindow->mapToGlobal(QPoint(m_loginWindow->width() / 2 - 35, m_loginWindow->height() + 100));

    //判断输入是否合理
    if(!m_usermanager->isUserNameRight(name) || !m_usermanager->isPassWordRight(pwd))
    {
        //显示提示信息
        QToolTip::showText(pos, "用户名或密码长度不正确", this, this->rect(), 5000);
        return;
    }

    if(ret == 3 || ret == 2) //用户存在
    {
        //显示提示信息
        QToolTip::showText(pos, "用户已存在", this, this->rect(), 5000);
    }
    else //注册成功
    {
        //显示提示信息
        QToolTip::showText(pos, "注册成功，自动登录", this, this->rect(), 5000);

        //自动登录
        this->m_userName = name;
        this->m_password = pwd;

        this->show();
        m_loginWindow->close();
        delete m_loginWindow;
        m_loginWindow = nullptr;

        //添加用户信息
        this->m_usermanager->addUser(this->m_userName, this->m_password);
    }
}

//用户点击联机模式
void MainScene::onOnlineTriggerd()
{
    this->m_onlineWindow = new OnlineWindow(this);
    m_onlineWindow->show();

    //监听是否连接成功
    connect(m_onlineWindow, &OnlineWindow::connectSuccessfully, this, [ = ]()
    {
        m_isOnlineMode = true;
        m_onlineWindow->hide();
    });

    //监听断开连接
    connect(m_onlineWindow, &OnlineWindow::disConnect, this, [ = ]()
    {
        m_isOnlineMode = false;
        //m_onlineWindow->disconnectOnline();
        QMessageBox::about(this, "联机提醒", "对手断开联机模式");
    });

    //监听对方进入游戏
    connect(m_onlineWindow, &OnlineWindow::rivalEnterGame, this, [ = ](int gameLevel)
    {
        enterGameScene(gameLevel, onlineMode);
    });
}

//用户断开联机
void MainScene::onDisconnectTriggerd()
{
    if(m_onlineWindow)
    {
        m_onlineWindow->write("DISCONNECT");
        m_onlineWindow->disconnectOnline();
    }

    QMessageBox::about(this, "联机提示", "已经断开联机");
}

MainScene::~MainScene()
{
    delete ui;

    if(m_usermanager)
    {
        delete m_usermanager;
        m_usermanager = nullptr;
    }

    if(m_loginWindow)
    {
        m_loginWindow->deleteLater();
        m_loginWindow = nullptr;
    }
}

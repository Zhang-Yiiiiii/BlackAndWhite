#include "mainscene.h"

#include <QGraphicsOpacityEffect>
#include <QToolBar>
#include <QBuffer>
#include "lightoutgame.h"
#include "antgame.h"
#include "animator.h"
#include "mypushbutton.h"
#include "userutils.h"
#include <QStandardPaths>

//----------------------------------构造和析构--------------------------------------------
MainScene::MainScene(QWidget *parent)
    : BaseWindow(parent), m_gameScene(nullptr)
{

    this->setWindowIcon(QIcon(MYICON));

    QPoint pos(350, 100);

    QLabel* temp1 = new QLabel(this);
    QLabel* temp2 = new QLabel(this);

    QFont font("华文新魏", 40);
    font.setBold(true);
    temp1->setFont(font);
    temp1->setText("不要黑块");
    temp1->setStyleSheet("color : black; ");
    temp1->setFixedSize(230, 45);
    temp1->setAlignment(Qt::AlignCenter);
    temp1->move(pos);

    pos.setX(1000);
    font.setBold(true);
    temp2->setFont(font);
    temp2->setText("兰顿蚂蚁");
    temp2->setStyleSheet("color : black; ");
    temp2->setFixedSize(230, 45);
    temp2->setAlignment(Qt::AlignCenter);
    temp2->move(pos);

    //登录
    QAction* loginAction = m_startMenu->addAction("登录");
    loginAction->setIcon(QIcon(LOGINICONPATH));
    connect(loginAction, &QAction::triggered, this, &MainScene::onLoginClicked);

    m_gameMenu->addSeparator(); //分割线

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
    onlineAction->setIcon(QIcon(CONNECTICONPAHT));
    connect(onlineAction, &QAction::triggered, this, &MainScene::onOnlineTriggerd);

    //断开联机
    QAction* disconnectAction = m_toolMenu->addAction("断开联机");
    disconnectAction->setIcon(QIcon(DISCONNECTICONPATH));
    connect(disconnectAction, &QAction::triggered, this, &MainScene::onDisconnectTriggerd);

    //初始化用户管理员
    this->m_usermanager = new UserManager;

    //初始化选关按钮
    initSelectBtn();

    //显示选关六边形
    showSelectBtn();

    //设置动画
    //setAnimations();

    //设置音乐播放器
    setMusicPlayer(new MusicPlayer(this));

    m_currentUser = UserUtils::findUserByName(m_userName);

    // 你应该已经在构造函数中获取 currentUser（比如从登录页面传入）
    m_avatarWidget = new AvatarWidget(m_currentUser, this);
    m_avatarWidget->move(40, 40);  // 左上角
    m_avatarWidget->show();

}

MainScene::~MainScene()
{
    if(m_usermanager)
    {
        delete m_usermanager;
        m_usermanager = nullptr;
    }

    // if(m_loginWindow)
    // {
    // m_loginWindow->deleteLater();
    // }

}

//----------------------------------私有方法--------------------------------------------

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
    const int length = Hexagon::getSideLength();

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
    y = 200;
    int level = ANTGAMENUMBER;

    const int rows = 5;

    for(int i = 0; i < rows; i++)
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

//设置动画
void MainScene::setAnimations()
{
    for(auto btn : m_selectBtns)
    {
        Animator * ani = Animator::createAnimator(btn, Animator::SlideFromTop);
        ani->start();
    }
}

//进入游戏场景
void MainScene::enterGameScene(int gameLevel, BuildWay enterWay, int gameStep, int bugX, int bugY, int bugDirection)
{
    if(gameLevel <= ANTGAMENUMBER) //兰顿蚂蚁模式
    {
        //不指定父窗口 不然图标不显示

        m_gameScene = new AntGame(gameLevel, m_userName, this->m_usermanager, nullptr, enterWay);

    }
    else if(gameLevel <= SELECTBTNNUMBER)   //熄灯游戏模式
    {
        m_gameScene = new LightOutGame(gameLevel, m_userName, this->m_usermanager, nullptr, enterWay);
    }

    m_gameScene->setMusicPlayer(m_musicPlayer); //设置音乐播放器

    Animator::transition(this, m_gameScene); //使用动画进入

    // 监听返回信号
    connect(m_gameScene, &AbstractGameScene::changeBack, this, &MainScene::onGameSceneChangeBack);

    if (enterWay == playMode) // 游戏模式
    {
        return;
    }
    else if (enterWay == startingPointMode || enterWay == destinationMode || enterWay == lightBuildMode)  // 自建图模式
    {
        // 隐藏提交按钮
        m_gameScene->hideSubmitBtn();

        //显示随机生成地图按钮
        m_gameScene->showRandomBtn();

        // 创建保存按钮
        createSaveButton(gameStep, bugX, bugY, bugDirection, enterWay);
    }
    else if(enterWay == onlineMode)    // 联机模式
    {
        setOnlineMode();
    }
}

//显示登录对话框
void MainScene::showLoginWindow()
{

    if(!m_loginWindow)
    {
        m_loginWindow = new LoginWindow(this);    //不指定父窗口，否则主窗口隐藏时 登录界面也会隐藏
    }

    m_loginWindow->setWindowIcon(QIcon(MYICON));
    m_loginWindow->move((this->width() - m_loginWindow->width()) / 2, (this->height() - m_loginWindow->height()) / 2);

    m_loginWindow->show();

    //关闭对话框时重新显示主页面
    //connect(m_loginWindow, &LoginWindow::userClose, this, &MainScene::show, Qt::UniqueConnection);
}

//自建ant地图
void MainScene::buildAntGame(BuildWay buildWay)
{
    // 显示对话框
    showBuildDialog(buildWay);
}

//自建light地图
void MainScene::buildLightGame()
{
    int level = QInputDialog::getInt(this, "建立熄灯游戏", "请输入关卡数38-52");

    if(level > SELECTBTNNUMBER || level <= ANTGAMENUMBER)    //判断关卡是否输入正确
    {
        QToolTip::showText(this->rect().center(), "关卡数不正确", this);
        return;
    }

    enterGameScene(level, lightBuildMode);
}

//显示建图对话框
void MainScene::showBuildDialog(BuildWay buildWay)
{
    //显示对话框
    if(!m_mappingDialog)
    {
        m_mappingDialog = new BuildMapDialog(this);
    }

    m_mappingDialog->show();

    //从对话框获取信息
    connect(m_mappingDialog, &BuildMapDialog::getedInfo, this, [this, buildWay]()
    {
        onMapingInfoReceived(buildWay);
    });
}

// 创建保存地图按钮
void MainScene::createSaveButton(int gameStep, int bugX, int bugY, int bugDirection, BuildWay buildWay)
{
    QPushButton *saveBtn = MyPushButton::createButton(MyPushButton::commonButton, "保存", m_gameScene);
    saveBtn->move(BACKGROUDWIDTH - saveBtn->width(), BACKGROUDHEIGHT - 4 * saveBtn->height());
    saveBtn->show();

    connect(saveBtn, &QPushButton::clicked, this, [this, gameStep, bugX, bugY, bugDirection, buildWay]()
    {
        onSaveButtonClicked(buildWay, gameStep, bugX, bugY, bugDirection);
    });
}

//设置联机模式
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

//----------------------------------私有槽--------------------------------------------

//选关按钮被点击
void MainScene::onHexagonClicked(int gameLevel)
{
    BuildWay mode = playMode;

    if(m_isOnlineMode)
    {
        mode = onlineMode;

        //联机模式 告诉对方也进入
        m_onlineWindow->write("ENTER_GAME" + QString::number(gameLevel).toLatin1())->flush();
    }

    enterGameScene(gameLevel, mode);
}

// 处理返回信号
void MainScene::onGameSceneChangeBack()
{
    m_gameScene->setInternalClose(true);  //确定是内部进行返回的

    Animator::transition(m_gameScene, this);

    // 在淡入完成后再销毁游戏场景
    connect(m_gameScene, &AbstractGameScene::sceneShow, this, [this]()
    {
        // 在主界面彻底显示后，再删掉旧的场景
        m_gameScene->deleteLater();
    });
}

//用户登录
void MainScene::onLoginClicked()
{
    //显示登录对话框
    showLoginWindow();

    //获取登录信息
    connect(m_loginWindow, &LoginWindow::userConfirmed, this, &MainScene::onUserConfirmLogin, Qt::UniqueConnection);

    //用户注册
    connect(m_loginWindow, &LoginWindow::userRegistered, this, &MainScene::onUserConfirmRegister, Qt::UniqueConnection);
}

//处理用户登录
void MainScene::onUserConfirmLogin()
{
    int ret = m_usermanager->verifyUserInfo(m_loginWindow->getUserName(), m_loginWindow->getUserPassword());

    //提示信息所在位置
    const QPoint pos = m_loginWindow->mapToGlobal(QPoint(m_loginWindow->width() / 2 - 35, m_loginWindow->height() + 100));

    if(ret == 3) //登录成功
    {
        //显示提示信息
        QToolTip::showText(pos, "登录成功", this, this->rect(), 5000);

        //记录用户信息
        m_userName = m_loginWindow->getUserName();
        m_password = m_loginWindow->getUserPassword();

        //this->show();
        m_loginWindow->close();
        //delete m_loginWindow;
        //m_loginWindow = nullptr;
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

        // this->show();
        m_loginWindow->hide();

        //m_loginWindow->deleteLater();

        //添加用户信息
        this->m_usermanager->addUser(this->m_userName, this->m_password);
    }
}

//从建图对话框中获取信息
void MainScene::onMapingInfoReceived(BuildWay buildWay)
{
    int gameLevel, gameStep, bugX, bugY, bugDirection;
    gameLevel = m_mappingDialog->getNum1();
    gameStep = m_mappingDialog->getNum2();
    bugX = m_mappingDialog->getNum3();
    bugY = m_mappingDialog->getNum4();
    bugDirection = m_mappingDialog->getNum5();

    //进入游戏场景
    enterGameScene(gameLevel, buildWay, gameStep, bugX, bugY, bugDirection);
}

// 处理保存地图按钮点击事件
void MainScene::onSaveButtonClicked(BuildWay buildWay, int gameStep, int bugX, int bugY, int bugDirection)
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

//用户点击联机模式
void MainScene::onOnlineTriggerd()
{
    if(!m_onlineWindow)
    {
        m_onlineWindow = new OnlineWindow(this);
    }

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
        m_onlineWindow->disconnectOnline();
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

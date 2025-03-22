#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH, BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));

    this->setAttribute(Qt::WA_DeleteOnClose);

    //初始化用户管理员
    this->m_usermanager = new UserManager;

    //设置菜单栏
    //显示游戏说明
    connect(this->ui->actioninstruction, &QAction::triggered, this, [this]()
    {
        this->m_gameScene->showRule();
    });

    //起点建图
    connect(this->ui->actionstartingPoint, &QAction::triggered, this, [this]()
    {
        this->selfBuildGame(startingPointMode); //起点建图
    });

    //终点建图
    connect(this->ui->actiondestination, &QAction::triggered, this, [ = ]()
    {
        this->selfBuildGame(destinationMode);  //终点建图
    });

    //退出游戏
    connect(this->ui->actionquit, &QAction::triggered, this, []()
    {
        exit(0);
    });

    //登录用户
    connect(this->ui->actionLogin, &QAction::triggered, this, &MainScene::onUserLogin);

    //显示选关六边形
    showSelectBtn();

    //进行联机
    connect(ui->online, &QAction::triggered, this, [ = ]()
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
        connect(m_onlineWindow->m_clientConnection, &QTcpSocket::disconnected, this, [ = ]()
        {
            m_isOnlineMode = false;
            QMessageBox::about(this, "提醒", "联机已断开");
        });

        //监听对方进入游戏
        connect(m_onlineWindow, &OnlineWindow::rivalEnterGame, this, [ = ](int gameLevel)
        {
            enterGameScene(gameLevel, onlineMode);
        });
    });
}

//重写绘图事件
void MainScene::paintEvent(QPaintEvent*)
{
    //实例化画家
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    //加载背景
    QPixmap pix;
    //pix = pix.scaled(this->size(),Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    pix.load(BACKGROUDPATH);
    painter.drawPixmap(0, 0, pix);
}

//显示选关六边形  监听进入游戏场景
void MainScene::showSelectBtn()
{
    //初始化六边形按钮
    for(int i = 0; i < SELECTBTNNUMBER; i++)
    {
        m_selectBtns[i] = new Hexagon(i);
        m_selectBtns[i]->setParent(this);

        //监听六边形被点击的信号  进入游戏场景
        connect(m_selectBtns[i], &Hexagon::beClicked, this, [ = ](int gameLevel)
        {
            onHexagonClicked(gameLevel);

            //联机模式 告诉对方也进入
            if(m_isOnlineMode)
            {
                m_onlineWindow->m_clientConnection->write("ENTER_GAME" + QString::number(gameLevel).toLatin1());
                m_onlineWindow->m_clientConnection->flush();
            }
        });
    }

    //六边形起始点
    int x = 950;
    int y = 200;
    int k = 1;  //每行个数
    int cnt = 4;  //计算每行六边形数量

    //显示上半部分
    for(int i = 0; i < 22; i++)
    {
        m_selectBtns[i]->move(x, y);

        x += 90;

        if(k % cnt == 0)
        {
            k = 0;
            y += 72;
            x -= (cnt + 1) * 85 - 15;
            cnt++;
        }

        k++;
    }

    x += 85;
    cnt = 6;
    k = 1;

    //显示下半部分
    for(int i = 22; i < 37; i++)
    {
        m_selectBtns[i]->move(x, y);

        x += 90;

        if(k % cnt == 0)
        {
            k = 0;
            y += 72;
            x -= (cnt) * 85 - 15;

            cnt--;
        }

        k++;
    }
}

//自建地图
void MainScene::selfBuildGame(gameMode buildWay)
{
    // 显示对话框
    showBuildDialog(buildWay);
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

// 进入游戏场景
void MainScene::enterGameScene(int gameLevel, gameMode enterWay, int gameStep, int bugX, int bugY, int bugDirection)
{
    m_gameScene = new GameScene(gameLevel, m_userName, this->m_usermanager, this);
    m_gameScene->m_gameMode = enterWay;  //标记游戏模式
    m_gameScene->setGeometry(this->geometry());
    this->hide();
    m_gameScene->show();

    // 监听返回信号
    connect(m_gameScene, &GameScene::changeBack, this, &MainScene::onGameSceneChangeBack);

    if (enterWay == playMode) //游戏模式
    {
        return;
    }
    else if (enterWay == startingPointMode || enterWay == destinationMode)  //自建图模式
    {
        //断开提交按钮
        m_gameScene->submitBtn->setDisabled(true);
        m_gameScene->submitBtn->hide();

        // 创建保存按钮
        createSaveButton(gameStep, bugX, bugY, bugDirection, enterWay);
    }
    else    //联机模式
    {
        //监听我方完成游戏的信号
        connect(m_gameScene, &GameScene::gameOver, this, [ = ](int totalTime)
        {
            m_onlineWindow->m_clientConnection->write("WIN_GAME" + QString::number(totalTime).toUtf8());
            m_onlineWindow->m_clientConnection->flush();

            m_isWeFinished = true;
        });

        //监听对方完成游戏的信号
        connect(m_onlineWindow, &OnlineWindow::rivalOverGame, this, [ = ](int totalTime)
        {
            if (totalTime < m_gameScene->getTotalTime())    //对方胜利
            {
                qDebug() << "dui方：" << totalTime << "  wo方： " << m_gameScene->getTotalTime();
                m_onlineWindow->m_clientConnection->write("YOU_WIN");
                m_onlineWindow->m_clientConnection->flush();
                QMessageBox::about(m_gameScene, "提醒", "对方胜利");
                emit m_gameScene->changeBack();
            }
            else if(m_isWeFinished) //我方胜利
            {
                m_onlineWindow->m_clientConnection->write("YOU_LOSE" + QString::number(totalTime).toUtf8());
                m_onlineWindow->m_clientConnection->flush();
                QMessageBox::about(m_gameScene, "提醒", "我方胜利");
                emit m_gameScene->changeBack();
            }
        });

        //监听我方赢得游戏
        connect(m_onlineWindow, &OnlineWindow::weWinGame, this, [ = ]()
        {
            QMessageBox::about(m_gameScene, "提醒", "我方已经胜利");
            emit m_gameScene->changeBack();
        });

        //监听我方输了游戏
        connect(m_onlineWindow, &OnlineWindow::weLoseGame, this, [ = ]()
        {
            QMessageBox::about(m_gameScene, "提醒", "对方胜利");
            emit m_gameScene->changeBack();
        });
    }
}

// 处理返回信号
void MainScene::onGameSceneChangeBack()
{
    this->setGeometry(m_gameScene->geometry());
    m_gameScene->hide();
    this->show();
}

//处理用户登录
void MainScene::onUserConfirmLogin(LoginWindow * loginWindow)
{
    int ret = this->m_usermanager->verifyUserInfo(loginWindow->getUserName(), loginWindow->getUserPassword());

    //提示信息所在位置
    QPoint pos = loginWindow->mapToGlobal(QPoint(loginWindow->width() / 2 - 35, loginWindow->height() + 100));

    if(ret == 3) //登录成功
    {
        //显示提示信息
        QToolTip::showText(pos, "登录成功", this, this->rect(), 5000);

        //记录用户信息
        this->m_userName = loginWindow->getUserName();
        this->m_password = loginWindow->getUserPassword();

        this->show();
        delete loginWindow;
        loginWindow = nullptr;
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

// 创建保存按钮
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

// 处理保存按钮点击事件
void MainScene::handleSaveButtonClicked(gameMode buildWay, int gameStep, int bugX, int bugY, int bugDirection)
{
    int ret = QMessageBox::question(this, "问题", "确定保存游戏？");

    if (ret == QMessageBox::Yes)
    {
        m_gameScene->saveGame(buildWay, gameStep, bugX, bugY, bugDirection);
    }
}

//显示登录对话框
LoginWindow* MainScene::showLoginWindow()
{
    LoginWindow * loginWindow = new LoginWindow();
    loginWindow->setWindowIcon(QIcon(MYICON));
    loginWindow->move((this->width() - loginWindow->width()) / 2, (this->height() - loginWindow->height()) / 2);

    this->hide();
    loginWindow->show();

    //关闭对话框时重新显示主页面
    connect(loginWindow, &LoginWindow::userClose, this, [ = ]() mutable
    {

        this->show();   //显示游戏界面

        delete loginWindow;
        loginWindow = nullptr;
    });

    return loginWindow;
}

//用户登录
void MainScene::onUserLogin()
{
    //显示登录对话框
    LoginWindow * loginWindow = showLoginWindow();

    //获取登录信息
    connect(loginWindow, &LoginWindow::userConfirmed, this, [this, loginWindow]()mutable
    {
        onUserConfirmLogin(loginWindow);
    });

    //用户注册
    connect(loginWindow, &LoginWindow::userRegistered, this, [this, loginWindow]() mutable
    {
        onUserConfirmRegister(loginWindow);
    });
}

//选关按钮被点击
void MainScene::onHexagonClicked(int gameLevel)
{
    gameMode mode = playMode;

    if(m_isOnlineMode)
    {
        mode = onlineMode;
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

    //判断信息是否正确

    //进入游戏场景
    enterGameScene(gameLevel, buildWay, gameStep, bugX, bugY, bugDirection);
}

//用户确定注册
void MainScene::onUserConfirmRegister(LoginWindow * loginWindow)
{
    int ret = this->m_usermanager->verifyUserInfo(loginWindow->getUserName(), loginWindow->getUserPassword());

    //提示信息所在位置
    QPoint pos = loginWindow->mapToGlobal(QPoint(loginWindow->width() / 2 - 35, loginWindow->height() + 100));

    if(ret == 3 || ret == 2) //用户存在
    {
        //显示提示信息
        QToolTip::showText(pos, "用户已存在", this, this->rect(), 5000);
    }
    else //注册成功
    {
        this->m_userName = loginWindow->getUserName();
        this->m_password = loginWindow->getUserPassword();

        //显示提示信息
        QToolTip::showText(pos, "注册成功，自动登录", this, this->rect(), 5000);

        this->show();
        delete loginWindow;
        loginWindow = nullptr;

        //添加用户信息
        this->m_usermanager->addUser(this->m_userName, this->m_password);
    }
}

MainScene::~MainScene()
{
    delete ui;

    delete m_usermanager;
    m_usermanager = nullptr;
}

#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH,BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));

    //设置菜单栏

    //显示游戏说明
    connect(this->ui->actioninstruction,&QAction::triggered,[=](){
        this->gameScene->showRule();
    });


    //起点建图
    connect(this->ui->actionstartingPoint,&QAction::triggered,[=](){
        this->selfBuildGame(false); //起点建图
    });

    //终点建图
    connect(this->ui->actiondestination,&QAction::triggered,[=](){
        this->selfBuildGame(true);  //终点建图
    });

    //退出游戏
    connect(this->ui->actionquit,&QAction::triggered,[=](){
        exit(0);
    });

    //登录用户
    connect(this->ui->actionLogin,&QAction::triggered,[=](){
        this->userLogin();
    });


    //初始化用户管理员
    this->usermanager = new UserManager;

    //显示选关六边形
    showSelectBtn();
}


//重写绘图事件
void MainScene::paintEvent(QPaintEvent *e)
{
    //实例化画家
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    //加载背景
    QPixmap pix;
    pix.load(BACKGROUDPATH);
    painter.drawPixmap(0,0,pix);

}

//显示选关六边形
void MainScene::showSelectBtn()
{
    //初始化六边形按钮
    for(int i=0;i<SELECTBTNNUMBER;i++)
    {
        selectBtns[i] = new Hexagon(i);
        selectBtns[i]->setParent(this);

        //监听六边形被点击的信号  进入游戏场景
        connect(selectBtns[i],&Hexagon::beClicked,[=](int gameLevel){
            gameScene = new GameScene(gameLevel,usermanager,this);
            this->hide();
            gameScene->setGeometry(this->geometry());
            gameScene->show();

            //监听返回来的信号
            connect(gameScene,&GameScene::changeBack,[=](){
                gameScene->hide();
                this->setGeometry(gameScene->geometry());
                this->show();

                //手动释放
                delete gameScene;
                gameScene = nullptr;
            });
        });
    }

    //六边形起始点
    int x = 950;
    int y = 200;
    int k = 1;
    int cnt = 4;  //计算每行六边形数量

    //显示上半部分
    for(int i = 0;i < 22;i++)
    {
        selectBtns[i]->move(x,y);

        x+=90;
        if(k%cnt == 0)
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
    for(int i = 22;i < 37;i++)
    {
        selectBtns[i]->move(x,y);

        x += 90;
        if(k%cnt == 0)
        {
            k = 0;
            y += 72;
            x -= (cnt)*85 - 15;

            cnt--;
        }
        k++;
    }
}

//自建地图
void MainScene::selfBuildGame(bool buildWay)
{
    mydialog = new myDialog(this);
    mydialog->show();

    connect(mydialog,&myDialog::getedInfo,[=](){
        int gameLevel,gameStep,bugX,bugY,bugDirection;
        gameLevel = mydialog->num1;
        gameStep = mydialog->num2;
        bugX = mydialog->num3;
        bugY = mydialog->num4;
        bugDirection = mydialog->num5;

        //进入游戏场景 由玩家自行改变地图
        gameScene = new GameScene(gameLevel,this->usermanager,this);
        this->hide();
        gameScene->setGeometry(this->geometry());
        gameScene->show();

        //返回来的信号
        connect(gameScene,&GameScene::changeBack,[=](){
            gameScene->hide();
            this->setGeometry(gameScene->geometry());
            this->show();

            delete gameScene;
            gameScene = nullptr;
        });

        //保存自建地图
        //保存按钮
        QPushButton * saveBtn = new QPushButton(gameScene);
        saveBtn->setText("保 存");
        saveBtn->setFont(QFont("华文新魏",15));
        saveBtn->setFixedSize(120,50);
        saveBtn->move(BACKGROUDWIDTH-saveBtn->width(),BACKGROUDHEIGHT- 4 * saveBtn->height());
        saveBtn->show();
        connect(saveBtn,&QPushButton::clicked,[=](){
            int ret = QMessageBox::question(this,"问题","确定保存游戏？");
            if(ret == QMessageBox::Yes)
            {
                this->gameScene->saveGame(buildWay,gameStep,bugX,bugY,bugDirection);
            }
        });
    });
}

//用户登录
void MainScene::userLogin()
{
    //登录对话框
    LoginWindow * loginWindow = new LoginWindow();
    loginWindow->setWindowIcon(QIcon(MYICON));
    loginWindow->move((this->width()-loginWindow->width())/2,(this->height()-loginWindow->height())/2);
    loginWindow->show();
    this->hide();


    //获取登录信息
    connect(loginWindow,&LoginWindow::userConfirmed,[=]()mutable{
        int ret = this->usermanager->verifyUserInfo(loginWindow->userName,loginWindow->password);

        //提示信息所在位置
        QPoint pos = loginWindow->mapToGlobal(QPoint(loginWindow->width()/2 - 35,loginWindow->height() + 100));

        if(ret == 3) //登录成功
        {
            //显示提示信息
            QToolTip::showText(pos,"登录成功",this,this->rect(),5000);

            //记录用户信息
            this->m_userName = loginWindow->userName;
            this->m_password = loginWindow->password;

            this->show();
            delete loginWindow;
            loginWindow = nullptr;
        }
        else if(ret == 2) //密码错误
        {
            //显示提示信息
            QToolTip::showText(pos,"密码错误",this,this->rect(),5000);
        }
        else //用户不存在
        {
            //显示提示信息
            QToolTip::showText(pos,"用户不存在",this,this->rect(),5000);
        }
    });
}

void MainScene::userRegister()
{

}


MainScene::~MainScene()
{
    delete ui;
}

#include "mainscene.h"
#include "ui_mainscene.h"
#include "gridbutton.h"

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
    //起点建图
    connect(this->ui->actionstartingPoint,&QAction::triggered,[=](){
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
            gameScene = new GameScene(gameLevel,this);
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
                    this->gameScene->saveGame(gameLevel,gameStep,bugX,bugY,bugDirection);
                }
            });

        });

    });

    //终点建图
    connect(this->ui->actiondestination,&QAction::triggered,[=](){

    });

    //退出游戏
    connect(this->ui->actionquit,&QAction::triggered,[=](){
        exit(0);
    });

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
            gameScene = new GameScene(gameLevel,this);
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
        });
    }


    //六边形起始点
    int x = 950;
    int y = 200;
    int k = 1;
    int cnt = 4;  //计算每行六边形数量

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

MainScene::~MainScene()
{
    delete ui;
}

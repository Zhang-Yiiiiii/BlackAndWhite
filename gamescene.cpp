#include "gamescene.h"

GameScene::GameScene(int gameLevel ,QWidget *parent)
    : QMainWindow{parent},gameLevel(gameLevel)
{
    data = new Data;

    for(int i = 0;i<20;i++)
    {
        for(int j = 0;j<20;j++)
        {

            gameArray[i][j] = data->gameArray[gameLevel][i][j];
            ansArray[i][j] = data->ansArray[gameLevel][i][j];
        }
    }

    //初始化虫子所在位置、方向 750 400 游戏步数
    bugPos.setX(data->bugPos[gameLevel].x());
    bugPos.setY(data->bugPos[gameLevel].y());
    bugDir = data->bugDir[gameLevel];
    gameStep = data->stepArray[gameLevel];


    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH,BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));

    //设置菜单栏
    QMenuBar * menubar = menuBar();
    menubar->setParent(this);
    menubar->setStyleSheet("font: 700 12pt \"Microsoft YaHei UI\";\nbackground-color: rgba(217, 217, 217, 150);\ncolor: rgb(66, 66, 66);");

    QMenu * startMenu = menubar->addMenu("开始");
    QMenu * gameMenu = menubar->addMenu("游戏");
    QMenu * toolMenu = menubar->addMenu("工具");

    QAction * quitAction = startMenu->addAction("退出");
    QAction * saveAction = startMenu->addAction("保存");

    QAction * buildAction = gameMenu->addAction("自建游戏地图");
    QAction * instructionAction = gameMenu->addAction("说明");


    //退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        exit(0);
    });

    //设置返回按钮
    QPushButton * backBtn = new QPushButton(this);
    backBtn->setText("返 回");
    backBtn->setFont(QFont("华文新魏",15));
    backBtn->setFixedSize(120,50);
    backBtn->move(BACKGROUDWIDTH-backBtn->width(),BACKGROUDHEIGHT-backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
        emit changeBack();
    });

    //设置提交按钮
    QPushButton * submitBtn = new QPushButton(this);
    submitBtn->setText("提 交");
    submitBtn->setFont(QFont("华文新魏",15));
    submitBtn->setFixedSize(120,50);
    submitBtn->move(BACKGROUDWIDTH-submitBtn->width(),BACKGROUDHEIGHT - 2 * submitBtn->height());
    connect(submitBtn,&QPushButton::clicked,[=](){
        //判断是否胜利
        std::cout.flush();
        std::cout<<"ans\n";
        std::cout.flush();
        if(isWin())
        {
            qDebug()<<"胜利";
        }
        else
        {
            qDebug()<<"失败";
        }
        std::cout.flush();
    });


    //重置按钮
    QPushButton * resetBtn = new QPushButton(this);
    resetBtn->setText("重 置");
    resetBtn->setFont(QFont("华文新魏",15));
    resetBtn->setFixedSize(120,50);
    resetBtn->move(BACKGROUDWIDTH-resetBtn->width(),BACKGROUDHEIGHT- 3 * resetBtn->height());
    connect(resetBtn,&QPushButton::clicked,[=](){
        int ret = QMessageBox::question(this,"问题","是否确定重置？重置将会被惩罚30秒");
        if(ret == QMessageBox::Yes)
        {
            for(int i = 0;i<20;i++)
            {
                for(int j = 0;j<20;j++)
                {
                    if(gameArray[i][j] != data->gameArray[gameLevel][i][j])  //有些格子被点击了
                    {
                        board[i][j]->changeFlag();
                        gameArray[i][j] = data->gameArray[gameLevel][i][j];
                    }
                }
            }
        }
    });


    // //设置打印按钮  测试
    // QPushButton * printBtn = new QPushButton(this);
    // printBtn->setText("打 印");
    // printBtn->setFont(QFont("华文新魏",15));
    // printBtn->setFixedSize(120,50);
    // printBtn->move(BACKGROUDWIDTH-printBtn->width(),BACKGROUDHEIGHT-printBtn->height());
    // connect(printBtn,&QPushButton::clicked,[=](){
    //     for(int i=0;i<20;i++)
    //     {
    //         for(int j=0;j<20;j++)
    //         {
    //             qDebug()<<gameArray[i][j];
    //         }
    //         qDebug()<<"\n";
    //     }
    // });


    //显示棋盘
    showBoard();


    //显示虫子
    QPushButton * bugBtn = new QPushButton(this);
    bugBtn->move(BOARDPOSX+bugPos.x()*(GRIDSIZE + 1),BOARDPOSY+bugPos.y()*(GRIDSIZE + 1));
    QString pixStr = QString(BUGPATH).arg(bugDir);
    bugPix.load(pixStr);
    bugBtn->setFixedSize(bugPix.size());
    bugBtn->setIconSize(bugPix.size());
    bugBtn->setIcon(QIcon(bugPix));
    bugBtn->setAttribute(Qt::WA_TransparentForMouseEvents);  //设置可以透明点击
    bugBtn->setEnabled(false);  //设置不能点击
    bugBtn->setStyleSheet("QPushButton{border:0px}");  //设置不规则图形


    //判断是否可解 并打印答案
    endIsSolvable(gameArray,bugPos,bugDir,gameStep);
}

//显示棋盘的函数
void GameScene::showBoard()
{
    int x = BOARDPOSX;
    int y = BOARDPOSY;

    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {

            board[i][j] = new GridButton(gameArray[i][j],this);
            //board[i][j]->flag = gameArray[i][j]?true:false;

            board[i][j]->posx = i;
            board[i][j]->posy = j;

            //监听格子被点击时翻转
            connect(board[i][j],&QPushButton::clicked,[=](){
                //update();
                board[i][j]->changeFlag();
                gameArray[i][j]=!gameArray[i][j];
            });

            board[i][j]->move(x,y);
            x += GRIDSIZE + 1;
        }
        x = BOARDPOSX;
        y += GRIDSIZE + 1;
    }
}

//重写绘图事件
void GameScene::paintEvent(QPaintEvent *e)
{
    //实例化画家
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    //加载背景
    QPixmap pix;
    pix.load(BACKGROUDPATH);
    painter.drawPixmap(0,0,pix);

}

//判断是否胜利
bool GameScene::isWin()
{

    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if(ansArray[i][j]!=gameArray[i][j])
                return false;
        }
    }
    return true;
}

//判断是否有解  已知起点
bool GameScene::startIsSolvable(bool gameArray[][20], QPoint pos, int bugDir, int step)
{
    bool gameArr[20][20];

    //拷贝数组
    for(int i = 0;i < 20; i++)
    {
        for(int j = 0;j < 20;j++)
        {
            gameArr[i][j] = gameArray[i][j];
        }
    }

    int x = pos.x();
    int y = pos.y();

    //模拟前进过程
    // 1 向前走一步 step--
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转
    // 3 改变前一个格子颜色


    while(step--)
    {
        //改变前一格颜色
        gameArr[x][y] = !gameArr[x][y];

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
        if(gameArr[x][y])  //白色
        {
            bugDir++; //右转方向加一
            bugDir%=4;
        }
        else
        {
            bugDir--;  //左转方向减一
            if(bugDir<0) bugDir+=4;
        }

        //跃出格子
        if(x >= 20 || x < 0 || y<0||y>=20)
        {
            return false;
        }
    }


    //将答案打印
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            std::cout.flush();
            std::cout<<gameArr[i][j]<<",";
        }
        std::cout<<"\n";
        std::cout.flush();
    }

    return true;
}


//判断是否有解  已知终点
bool GameScene::endIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step)  //棋盘 虫子位置 方向 步数
{
    bool gameArr[20][20];

    //拷贝数组
    for(int i = 0;i < 20; i++)
    {
        for(int j = 0;j < 20;j++)
        {
            gameArr[i][j] = gameArray[i][j];
        }
    }

    //测试代码
    // for(int i = 0;i < 20; i++)
    // {
    //     for(int j = 0;j < 20;j++)
    //     {
    //         qDebug()<<(gameArr[i][j]?"1":"0");
    //     }
    //     qDebug()<<"\n";
    // }

    int x = pos.x();
    int y = pos.y();

    //模拟后退过程
    // 1 将最后一个格子改变颜色 方便统一操作
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转 （黑色意味着之前是白色，当时右转，现在左转回来）
    // 3 后退一步，前一步格子颜色改变 step--

    gameArr[x][y] = !gameArr[x][y]; //改变最后一格颜色


    while(step--)
    {
        if(gameArr[x][y])  //白色
        {
            bugDir++; //右转方向加一
            bugDir%=4;
        }
        else
        {
            bugDir--;  //左转方向减一
            if(bugDir<0) bugDir+=4;
        }

        //改变前一格颜色
        gameArr[x][y] = !gameArr[x][y];

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
        if(x >= 20 || x < 0 || y<0||y>=20)
        {
            return false;
        }
    }

    //将第一格的颜色改变
    gameArr[x][y] = !gameArr[x][y];

    //将答案打印
    // for(int i=0;i<20;i++)
    // {
    //     for(int j=0;j<20;j++)
    //     {
    //         std::cout.flush();
    //         std::cout<<gameArr[i][j]<<",";
    //     }
    //     std::cout<<"\n";
    //     std::cout.flush();
    // }

    return true;
}


//保存自建地图
void GameScene::saveGame(int level,int step,int x,int y,int direction)
{

    int ret = QMessageBox::question(this,"询问","是否决定保存新建地图");

    if(ret == QMessageBox::No) return;

    //保存步数
    data->stepArray[level] = step;

    //保存bug位置 方向
    data->bugPos[level] = QPoint(x,y);
    data->bugDir[level] = direction;

    //将地图保存到data中
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            data->gameArray[level][i][j] = this->gameArray[i][j];
            data->ansArray[level][i][j] = this->ansArray[i][j];
        }
    }

    //进行返回操作
    emit changeBack();
}


GameScene::~GameScene()
{

    //删除数据对象
    // delete data;
    // data = nullptr;
}

#include "gamescene.h"

GameScene::GameScene(int gameLevel , QString userName, UserManager * usermanager, QWidget *parent)
    : QMainWindow{parent},gameLevel(gameLevel),usermanager(usermanager),userName(userName)
{
    //对本关的用户进行排序
    usermanager->userSort(gameLevel);

    //设置关闭即释放
    this->setAttribute(Qt::WA_DeleteOnClose);

    //初始化定时器
    showTimer = new QTimer(this);
    showTimer->start(500);

    timer = new QElapsedTimer;
    timer->start();

    //监听showTimer对用户通关时间进行更新
    connect(showTimer,&QTimer::timeout,this,&GameScene::updateTime);



    //显示用时的label
    timeLabel = new QLabel(this);
    timeLabel->setFixedWidth(200);
    timeLabel->setText("所用时间：00:00:00");
    timeLabel->move(150,400);
    timeLabel->setStyleSheet("QLabel { font-family: '华文新魏'; "
                             "font-weight: bold; "
                             "font-size: 20px; color: #333333; "
                             "background-color: #ffffff; "
                             "border: 2px solid #ffffff; "
                             "border-radius: 10px; }");

    timeLabel->setAlignment(Qt::AlignCenter);

    //罚时label
    timePenaltyLabel = new QLabel(this);
    timePenaltyLabel->setFixedWidth(200);
    timePenaltyLabel->setText("所罚时间：00:00:00");
    timePenaltyLabel->move(150,400 + timeLabel->height() + 10);
    timePenaltyLabel->setStyleSheet("QLabel { font-family: '华文新魏'; "
                             "font-weight: bold; "
                             "font-size: 20px; color: #333333; "
                             "background-color: #ffffff; "
                             "border: 2px solid #ffffff; "
                             "border-radius: 10px; }");

    timePenaltyLabel->setAlignment(Qt::AlignCenter);



    //初始化游戏信息对象
    data = new Data;

    //初始化信息
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

    //QAction * buildAction = gameMenu->addAction("自建游戏地图");
    QAction * instructionAction = gameMenu->addAction("说明");
    QAction * rankAction = gameMenu->addAction("排行榜");

    //连接排行榜按钮
    connect(rankAction,&QAction::triggered,[=](){
        this->showRankList();
    });



    //显示游戏说明
    connect(instructionAction,&QAction::triggered,[=](){
        this->showRule();
    });

    //退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        exit(0);
    });

    //设置返回按钮
    backBtn = new QPushButton(this);
    backBtn->setText("返 回");
    backBtn->setFont(QFont("华文新魏",15));
    backBtn->setFixedSize(120,50);
    backBtn->move(BACKGROUDWIDTH-backBtn->width(),BACKGROUDHEIGHT-backBtn->height());
    connect(backBtn,&QPushButton::clicked,[=](){
        emit changeBack();
    });

    //设置提交按钮
    submitBtn = new QPushButton(this);
    submitBtn->setText("提 交");
    submitBtn->setFont(QFont("华文新魏",15));
    submitBtn->setFixedSize(120,50);
    submitBtn->move(BACKGROUDWIDTH-submitBtn->width(),BACKGROUDHEIGHT - 2 * submitBtn->height());
    connect(submitBtn,&QPushButton::clicked,[=](){
        //判断是否胜利
        if(isWin())
        {
            QMessageBox::about(this,"通过","恭喜你成功通过此关");
            saveTotalTime();
            emit changeBack();  //进行返回
        }
        else
        {
            QMessageBox::about(this,"失败","答案错误，罚时30秒");
            this->resetGame(); //重置棋盘

            this->penaltyTime+=30; //罚时增加
        }
    });


    //重置按钮
    resetBtn = new QPushButton(this);
    resetBtn->setText("重 置");
    resetBtn->setFont(QFont("华文新魏",15));
    resetBtn->setFixedSize(120,50);
    resetBtn->move(BACKGROUDWIDTH-resetBtn->width(),BACKGROUDHEIGHT- 3 * resetBtn->height());
    connect(resetBtn,&QPushButton::clicked,[=](){
        int ret = QMessageBox::question(this,"问题","是否确定重置？");
        if(ret == QMessageBox::Yes)
        {
            for(int i = 0;i<20;i++)
            {
                this->resetGame(); //进行重置
            }
        }
    });


    //步数说明
    QLabel * stepLabel = new QLabel(this);
    stepLabel->setText(QString::number(this->gameStep));
    stepLabel->move(40,40);
    QFont stepLabelFont;
    stepLabelFont.setBold(true);
    stepLabelFont.setPointSize(12);
    stepLabel->setFont(stepLabelFont);


    //显示棋盘
    showBoard();

    //显示虫子
    showBug();

}

//显示游戏说明
void GameScene::showRule()
{
    std::ifstream ifs(RULEPATH);

    // 打开文件
    if (!ifs.is_open()) {
        QMessageBox::about(this,"通知",QString("无法打开文件").arg(RULEPATH));
        return;
    }

    // 使用 std::stringstream 读取整个文件内容
    std::stringstream buffer;
    buffer << ifs.rdbuf(); // 将文件内容读取到 stringstream 中

    //关闭文件
    ifs.close();

    // 将 stringstream 的内容转换为 QString
    QString fileContent = QString::fromStdString(buffer.str());

    QMessageBox::about(this,"说明",fileContent);
}

//显示排行榜
void GameScene::showRankList()
 {
    RankList * rankWindow = new RankList(this->usermanager->rankList,this);
    rankWindow->move(20,70);
    rankWindow->show();

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

//显示虫子
void GameScene::showBug()
{
    QPushButton * bugBtn = new QPushButton(this);

    //虫子所在坐标轴与窗口长宽不对应
    bugBtn->move(BOARDPOSX+bugPos.y()*(GRIDSIZE + 1),BOARDPOSY+bugPos.x()*(GRIDSIZE + 1));
    QString pixStr = QString(BUGPATH).arg(bugDir);
    bugPix.load(pixStr);
    bugBtn->setFixedSize(bugPix.size());
    bugBtn->setIconSize(bugPix.size());
    bugBtn->setIcon(QIcon(bugPix));
    bugBtn->setAttribute(Qt::WA_TransparentForMouseEvents);  //设置可以透明点击
    bugBtn->setEnabled(false);  //设置不能点击
    bugBtn->setStyleSheet("QPushButton{border:0px}");  //设置不规则图形
}

//重写绘图事件
void GameScene::paintEvent(QPaintEvent *)
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

//重置棋盘
void GameScene::resetGame()
{
    for(int i=0;i<20;i++)
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

//判断是否有解  已知起点信息
bool GameScene::startIsSolvable(bool gameArray[][20], QPoint pos, int bugDir, int step)
{
    bool gameArr[20][20];
    int tempStep = step;

    //起点
    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0;i < 20; i++)
    {
        for(int j = 0;j < 20;j++)
        {
            gameArr[i][j] = gameArray[i][j];
        }
    }


    //模拟前进过程
    // 1 向前走一步 step--
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转
    // 3 改变前一个格子颜色
    while(tempStep--)
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
            bugDir+=3;  //左转方向加三
            bugDir%=4;
        }

        //跃出格子
        if(x >= 20 || x < 0 || y<0||y>=20)
        {
            return false;
        }
    }

    //将结果传给data
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            this->data->gameArray[gameLevel][i][j] = gameArr[i][j];
            this->data->ansArray[gameLevel][i][j] = gameArray[i][j];
        }
    }

    this->data->bugDir[gameLevel] = bugDir;
    this->data->bugPos[gameLevel] = QPoint(x,y);
    this->data->stepArray[gameLevel] = step;

    return true;
}


//判断是否有解  已知终点
bool GameScene::endIsSolvable(bool gameArray[][20],QPoint pos,int bugDir,int step)  //棋盘 虫子位置 方向 步数
{
    bool gameArr[20][20];
    int tempStep = step;
    int dir = bugDir;

    int x = pos.x();
    int y = pos.y();

    //拷贝数组
    for(int i = 0;i < 20; i++)
    {
        for(int j = 0;j < 20;j++)
        {
            gameArr[i][j] = gameArray[i][j];
        }
    }


    //模拟后退过程
    // 1 将最后一个格子改变颜色 方便统一操作
    // 2 根据所在位置的格子颜色改变方向 黑色左转 白色右转 （黑色意味着之前是白色，当时右转，现在左转回来）
    // 3 后退一步，前一步格子颜色改变 step--
    gameArr[x][y] = !gameArr[x][y]; //改变最后一格颜色

    while(tempStep--)
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

    //将答案保存
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            this->data->gameArray[gameLevel][i][j] = gameArray[i][j];
            this->data->ansArray[gameLevel][i][j] = gameArr[i][j];
        }
    }

    this->data->bugDir[gameLevel] = dir;
    this->data->bugPos[gameLevel] = pos;
    this->data->stepArray[gameLevel] = step;

    return true;
}


//保存自建地图 buildWay==0：起点建图  buildWay==1：终点建图
void GameScene::saveGame(bool buildWay,int step,int x,int y,int direction)
{
    //判断是否可解 并且保存地图
    if(buildWay == 0) //起点建图
    {
        if(!startIsSolvable(this->gameArray,QPoint(x,y),direction,step))  //不可解
        {
            QMessageBox::about(this,"提醒","该设计游戏无解！请重新设计");
            return;
        }
    }
    else  //终点建图
    {
        if(!endIsSolvable(this->gameArray,QPoint(x,y),direction,step))  //不可解
        {
            QMessageBox::about(this,"提醒","该设计游戏无解！请重新设计");
            return;
        }
    }
    //进行返回操作
    emit changeBack();
}

//保存总用时
void GameScene::saveTotalTime()
{
    //计算总时间
    int totalTime = timer->elapsed()/1000;
    totalTime += penaltyTime;

    //更新时间
    usermanager->updatePassTime(this->userName,totalTime,this->gameLevel);
}

//更新时间
void GameScene::updateTime()
{
    int secs = timer->elapsed() / 1000;
    int mins = secs / 60;
    int hours = mins / 60;
    secs %= 60;
    mins %= 60;
    timeLabel->setText(QString::asprintf("所用时间：%02d:%02d:%02d", hours, mins, secs));

    secs = this->penaltyTime % 60;
    mins = penaltyTime/60;
    mins = mins %=60;
    hours = mins / 60;
    timePenaltyLabel->setText(QString::asprintf("所罚时间：%02d:%02d:%02d", hours, mins, secs));
}

GameScene::~GameScene()
{
    //删除数据对象
    delete data;
    data = nullptr;

    delete timer;
}

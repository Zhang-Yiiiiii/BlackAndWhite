#include "onlinewindow.h"
#include "ui_onlinewindow.h"

#include <QString>

OnlineWindow::OnlineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OnlineWindow)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::WindowModal); // 设置为模态窗口

    this->setFixedSize(517, 363);

    this->ui->labelLogin->setStyleSheet("QLabel { color: black; }");  // 设置字体颜色为黑色

    this->setWindowIcon(QIcon(MYICON));

    //设置透明度
    this->ui->ipLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->portLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->portEdit->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    this->ui->ipEdit->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    this->ui->listenBtn->setStyleSheet("background-color: rgba(255, 255, 255, 20);");
    this->ui->joinBtn->setStyleSheet("background-color: rgba(255, 255, 255, 20);");

    // 置于顶层
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    //设置默认ip和port
    this->ui->portEdit->setText("8888");
    this->ui->ipEdit->setText("127.0.0.1");

    //监听按钮的点击
    connect(ui->listenBtn, &QPushButton::clicked, this, &OnlineWindow::onListenBtnClicked); //创建房间
    connect(ui->joinBtn, &QPushButton::clicked, this, &OnlineWindow::onJoinBtnClicked); //加入房间

}

OnlineWindow::~OnlineWindow()
{
    delete ui;
}

void OnlineWindow::paintEvent(QPaintEvent*)
{

    QPainter painter(this);
    QPixmap loginPic;

    //画窗口背景
    loginPic.load(LOGINBACKGROUND);
    painter.drawPixmap(0, 0, loginPic.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //画白色背景
    // loginPic.load(LOGINWIHTEBACKGROUND);
    // painter.drawPixmap(15,17,loginPic);

    //画机器人图片
    loginPic.load(LOGINROBOT);
    painter.drawPixmap(260, 17, loginPic.width() - 15, loginPic.height() - 15, loginPic);
}

//作为服务端 监听连接
void OnlineWindow::onListenBtnClicked()
{
    //删除之前的套接字
    if(m_clientConnection)
    {
        m_clientConnection->close();
        delete m_clientConnection;
        m_clientConnection = nullptr;
    }

    if(!m_server)
    {
        m_server = new QTcpServer(this);
    }

    if(m_server->isListening())
    {
        QMessageBox::about(this, "提醒", "已经开创房间");
    }

    QString ip = ui->ipEdit->text();
    unsigned short port = ui->portEdit->text().toUShort();

    this->m_server->listen(QHostAddress(ip), port);

    connect(m_server, &QTcpServer::newConnection, this, [ = ]()
    {
        QMessageBox::about(this, "提醒", "连接成功");

        emit connectSuccessfully();

        this->hide();

        m_clientConnection = m_server->nextPendingConnection();

        //处理得到的信息
        connect(m_clientConnection, &QTcpSocket::readyRead, this, &OnlineWindow::handleInfo);
    });
}

//作为客服端 请求连接
void OnlineWindow::onJoinBtnClicked()
{
    //删除服务器
    if(!m_server)
    {
        m_clientConnection->close();
        delete m_clientConnection;
        m_clientConnection = nullptr;

        m_server->close();
        delete m_server;
        m_server = nullptr;
    }

    if(!m_clientConnection)
    {
        m_clientConnection = new QTcpSocket(this);
    }

    QString ip = ui->ipEdit->text();
    unsigned short port = ui->portEdit->text().toUShort();

    m_clientConnection->connectToHost(QHostAddress(ip), port);

    connect(m_clientConnection, &QTcpSocket::connected, this, [ = ]()
    {
        QMessageBox::about(this, "提醒", "连接成功");

        emit connectSuccessfully();

        this->hide();
    });
}

void OnlineWindow::handleInfo()
{
    QString data = m_clientConnection->readAll();

    //进入游戏
    if(data.startsWith("ENTER_GAME"))
    {
        const int numberPos = 10;
        const int gameLevel = data.mid(numberPos).toInt();
        emit rivalEnterGame(gameLevel);
    }
    else if(data.startsWith("WINGAME"))
    {
        const int timePos = 7;
        const int totalTime = data.mid(timePos).toInt();
        emit rivalOverGame(totalTime);
    }
    else if(data.startsWith("YOUWIN"))
    {
        emit weWinGame();
    }
}

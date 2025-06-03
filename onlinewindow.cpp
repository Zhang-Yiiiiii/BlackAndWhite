#include "onlinewindow.h"
#include "ui_onlinewindow.h"
#include "config.h"
#include "MessageTip.h"

#include <QString>
#include <QToolTip>

//----------------------------------构造析构--------------------------------------------

OnlineWindow::OnlineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OnlineWindow)
{
    ui->setupUi(this);

    //this->setWindowModality(Qt::WindowModal); // 设置为模态窗口

    this->setFixedSize(520, 400);   //设置大小
    setBackground(":/image/musicBackgnd.png");  //设置背景

    this->ui->labelLogin->setStyleSheet("QLabel { color: black; }");  // 设置字体颜色为黑色

    this->setWindowIcon(QIcon(MYICON)); //设置图标

    this->setWindowTitle("联机窗口");

    //设置透明度
    this->ui->ipLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->portLabel->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->portEdit->setStyleSheet("background-color: rgba(255, 255, 255, 0.2);");
    this->ui->ipEdit->setStyleSheet("background-color: rgba(255, 255, 255, 0.2);");
    this->ui->listenBtn->setStyleSheet("background-color: rgba(255, 255, 255, 20);");
    this->ui->joinBtn->setStyleSheet("background-color: rgba(255, 255, 255, 20);");

    // 置于顶层
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);

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

    cleanupConnections();
}

//----------------------------------公有方法--------------------------------------------

//写数据
OnlineWindow* OnlineWindow::write(const char* data)
{
    if(m_clientConnection && m_clientConnection->isOpen())
    {
        m_clientConnection->write(data);
        flush();
    }

    return this;
}

OnlineWindow* OnlineWindow::flush()
{
    if(m_clientConnection)
    {
        m_clientConnection->flush();
    }

    return this;
}

//断开联机
void OnlineWindow::disconnectOnline()
{
    cleanupConnections();
}

//设置背景
void OnlineWindow::setBackground(const QString file)
{

    QPixmap pix(file);
    QSize windowSize = this->size();
    QPixmap scalePix = pix.scaled(windowSize);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePix));

    this->setPalette(palette);

}

// 添加清理函数
void OnlineWindow::cleanupConnections()
{
    if (m_clientConnection)
    {
        m_clientConnection->disconnect();
        m_clientConnection->deleteLater();
        m_clientConnection = nullptr;
    }

    if (m_server)
    {
        m_server->close();
        delete m_server;
        m_server = nullptr;
    }
}

//----------------------------------私有槽--------------------------------------------

//作为服务端 监听连接
void OnlineWindow::onListenBtnClicked()
{
    // if(m_server && m_server->isListening())
    // {
    // QMessageBox::about(this, "提醒", "已经开创房间");
    // return;
    // }

    cleanupConnections();
    m_server = new QTcpServer(this);

    MessageTip::tip(this, "已经开创房间");

    //获取ip port
    QString ip = ui->ipEdit->text();
    unsigned short port = ui->portEdit->text().toUShort();

    this->m_server->listen(QHostAddress(ip), port);

    //连接成功
    connect(m_server, &QTcpServer::newConnection, this, [ = ]()
    {
        m_clientConnection = m_server->nextPendingConnection();
        emit connectSuccessfully();
        QMessageBox::about(this, "提醒", "连接成功");

        //处理得到的信息
        connect(m_clientConnection, &QTcpSocket::readyRead, this, &OnlineWindow::handleInfo);

        //监听断开连接
        connect(m_clientConnection, &QTcpSocket::disconnected, this, [ = ]()
        {
            m_clientConnection->deleteLater();
            m_clientConnection = nullptr; // 重要！
            emit disConnect();
        });
    });
}

//作为客服端 请求连接
void OnlineWindow::onJoinBtnClicked()
{
    cleanupConnections();
    m_clientConnection = new QTcpSocket(this);

    //获取ip port
    QString ip = ui->ipEdit->text();
    unsigned short port = ui->portEdit->text().toUShort();

    m_clientConnection->connectToHost(QHostAddress(ip), port);

    //连接成功
    connect(m_clientConnection, &QTcpSocket::connected, this, [ = ]()
    {
        emit connectSuccessfully();

        //处理得到的信息
        connect(m_clientConnection, &QTcpSocket::readyRead, this, &OnlineWindow::handleInfo);
        QMessageBox::about(this, "提醒", "连接成功");
    });
}

//处理收到的信息
void OnlineWindow::handleInfo()
{
    QString data = m_clientConnection->readAll();   //读取信息

    if (data.startsWith("ENTER_GAME"))
    {
        const int numberPos = 10;   //有效数据的起始位置
        bool ok;
        int gameLevel = data.mid(numberPos).toInt(&ok);

        if (ok)
        {
            emit rivalEnterGame(gameLevel);
        }
        else
        {
            QMessageBox::about(this, "提醒", "Invalid game level received");
        }
    }
    else if (data.startsWith("OVER_GAME"))
    {
        const int timePos = 9;  //有效数据的起始位置
        bool ok;
        int totalTime = data.mid(timePos).toInt(&ok);

        if (ok)
        {
            emit rivalOverGame(totalTime);
        }
        else
        {
            QMessageBox::about(this, "提醒", "Invalid time received");
        }
    }
    else if (data == "YOU_WIN")
    {
        emit weWinGame();
    }
    else if (data == "YOU_LOSE")
    {
        emit weLoseGame();
    }
    else if(data == "DISCONNECT")
    {
        disconnectOnline();
        emit disConnect();
    }
}

#ifndef ONLINEWINDOW_H
#define ONLINEWINDOW_H

#include <QMainWindow>
#include "config.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QPainter>

namespace Ui
{
    class OnlineWindow;
}

class OnlineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OnlineWindow(QWidget *parent = nullptr);
    ~OnlineWindow();

    OnlineWindow* write(const char* data);     //发送信息
    OnlineWindow* flush();

    //断开联机
    void disconnectOnline();

private:

    QString m_ip;
    unsigned short m_port;

    QTcpServer* m_server = nullptr;
    QTcpSocket* m_clientConnection = nullptr;

    //重写画图事件
    void paintEvent(QPaintEvent*) override;

signals:
    void connectSuccessfully();     //是否连接成功
    void rivalEnterGame(int gameLevel);  //对手进入游戏
    void rivalOverGame(int totalTime);   //对手完成游戏
    void weWinGame();   //我方赢得游戏
    void weLoseGame();  //我方输了游戏
    void disConnect();  //断开连接

private slots:
    void onListenBtnClicked();  //创建房间
    void onJoinBtnClicked();    //加入房间
    void handleInfo();          //处理得到的信息

private:
    Ui::OnlineWindow* ui;
};

#endif // ONLINEWINDOW_H

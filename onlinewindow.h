#ifndef ONLINEWINDOW_H
#define ONLINEWINDOW_H

/*****************************************************************
 * class: OnlineWindow （联机窗口）
 *
 * 用处: 实现P2P的联机功能、处理联机的对话
 *
 *****************************************************************/

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QPainter>

namespace Ui
{
    class OnlineWindow;
}

//处理获得的信息
class OnlineWindow : public QMainWindow
{
    Q_OBJECT

public:
    //------------------------构造析构----------------------------------

    explicit OnlineWindow(QWidget *parent = nullptr);
    ~OnlineWindow();

    //------------------------公有方法----------------------------------

    OnlineWindow* write(const char* data);     //发送信息
    OnlineWindow* flush();

    //断开联机
    void disconnectOnline();

    //设置背景
    void setBackground(const QString file);

private:
    //------------------------私有属性----------------------------------

    QString m_ip;
    unsigned short m_port;

    QTcpServer* m_server = nullptr;
    QTcpSocket* m_clientConnection = nullptr;

signals:
    //------------------------信号----------------------------------

    void connectSuccessfully();     //是否连接成功
    void disConnect();              //断开连接

    void rivalEnterGame(int gameLevel);  //对手进入游戏
    void rivalOverGame(int totalTime);   //对手完成游戏

    void weWinGame();   //我方赢得游戏
    void weLoseGame();  //我方输了游戏

private slots:
    //------------------------私有槽----------------------------------

    void onListenBtnClicked();  //创建房间
    void onJoinBtnClicked();    //加入房间

    //处理信息
    virtual void handleInfo();          //处理得到的信息

private:
    Ui::OnlineWindow* ui;
};

#endif // ONLINEWINDOW_H

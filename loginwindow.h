#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

/*
 * class: LoginWindow （登录窗口）
 *
 * 用处: 显示登录界面、显示注册界面、记录用户信息
 */

#include <QWidget>
#include "config.h"
#include <QPixmap>
#include <QPainter>



namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    //构造和析构
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    //获取用户名
    QString getUserName();

    //获取用户信息
    QString getUserPassword();


    //重写画图事件
    void paintEvent(QPaintEvent *) override;

private:
    //用户名
    QString m_userName;

    //用户密码
    QString m_password;

signals:
    void userConfirmed();  //用户点击登录按钮

    void userRegistered(); //用户点击注册按钮

private slots:
    void onLoginAccount();  //用户点击登录按钮

    void onRegisterAccount();  //用户点击确定注册按钮

    void onBack();  //用户点击返回按钮

    void onRequestRegister();  //用户点击请求注册按钮

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H

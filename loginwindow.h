#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

/*****************************************************************
 * class: LoginWindow （登录窗口）
 *
 * 用处: 显示登录界面、显示注册界面、记录用户信息
 *****************************************************************/

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDialog>

namespace Ui
{
    class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    //------------------------构造析构----------------------------------

    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    //------------------------公共方法----------------------------------

    //获取用户名
    QString getUserName();

    //获取用户信息
    QString getUserPassword();

    //设置背景
    void setBackground(const QString file);

    //------------------------保护方法----------------------------------

    //重写画图事件
    void paintEvent(QPaintEvent*) override;

    void closeEvent(QCloseEvent*) override;

    void checkPasswordLength(const QString &password);

private:
    //------------------------私有属性----------------------------------

    //用户名
    QString m_userName;

    //用户密码
    QString m_password;

signals:
    //------------------------信号----------------------------------

    void userConfirmed();  //用户点击登录按钮

    void userRegistered(); //用户点击注册按钮

    void userClose();   //用户点击关闭按钮

private slots:
    //------------------------私有槽----------------------------------

    void onLoginAccount();  //用户点击登录按钮

    void onRegisterAccount();  //用户点击确定注册按钮

    void onBack();  //用户点击返回按钮

    void onRequestRegister();  //用户点击请求注册按钮

private:
    Ui::LoginWindow* ui;
};

#endif // LOGINWINDOW_H

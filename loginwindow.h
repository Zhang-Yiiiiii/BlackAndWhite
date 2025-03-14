#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

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
    explicit LoginWindow(QWidget *parent = nullptr);

    //用户名
    QString userName;

    //用户密码
    QString password;

    //重写画图事件
    void paintEvent(QPaintEvent *) override;


    ~LoginWindow();

signals:
    void userConfirmed();  //用户点击登录按钮

    void userRegistered(); //用户点击注册按钮

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H

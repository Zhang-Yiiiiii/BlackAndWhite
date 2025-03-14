#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->setFixedSize(517,363);

    this->ui->labelLogin->setStyleSheet("QLabel { color: black; }");  // 设置字体颜色为黑色

    //设置用户名输入为黑色
    // QPalette palette = this->ui->userNameEdit->palette();
    // palette.setColor(QPalette::Text, Qt::black);  // 设置文本颜色为黑色
    // this->ui->userNameEdit->setPalette(palette);
    // this->ui->userNameEdit->setAutoFillBackground(true);  // 确保背景被填充

    //设置密码输入为黑色
    // palette = this->ui->passwdEdit->palette();
    // palette.setColor(QPalette::Text, Qt::black);  // 设置文本颜色为黑色
    // this->ui->passwdEdit->setPalette(palette);
    // this->ui->passwdEdit->setAutoFillBackground(true);  // 确保背景被填充

    //注册按钮为黑色


    //this->ui->framePic->setStyleSheet("background-image: url(:/image/loginRobot.jpg);");

    //设置边框
    this->ui->userNameEdit->setStyleSheet("QLineEdit { border: 2px solid black; border-radius: 5px; }");


    //设置透明度
    this->ui->labelPassword->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->labelUsername->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    this->ui->passwdEdit->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    this->ui->userNameEdit->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
    this->ui->loginButton->setStyleSheet("background-color: rgba(255, 255, 255, 20);");
    this->ui->registerButton->setStyleSheet("background-color: rgba(255, 255, 255, 20);");

    //置于顶层
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    //登录按钮的点击
    connect(this->ui->loginButton,&QPushButton::clicked,[=](){
        this->userName = this->ui->userNameEdit->text();
        this->password = this->ui->passwdEdit->text();
        emit this->userConfirmed();
    });

    //注册按钮的点击
    connect(this->ui->registerButton,&QPushButton::clicked,[=](){

    });


}

void LoginWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap loginPic;

    loginPic.load(LOGINBACKGROUND);
    painter.drawPixmap(0, 0, loginPic.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // loginPic.load(LOGINWIHTEBACKGROUND);
    // painter.drawPixmap(15,17,loginPic);

    loginPic.load(LOGINROBOT);
    painter.drawPixmap(260,17,loginPic);




}

LoginWindow::~LoginWindow()
{
    delete ui;
}

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::WindowModal); // 设置为模态窗口

    this->setFixedSize(517,363);

    this->ui->labelLogin->setStyleSheet("QLabel { color: black; }");  // 设置字体颜色为黑色

    this->setWindowIcon(QIcon(MYICON));

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

    // 置于顶层
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    // 登录/确定注册 按钮的点击
    connect(this->ui->loginButton,&QPushButton::clicked,this,&LoginWindow::loginAccount);

    //请求注册按钮的点击
    connect(this->ui->registerButton,&QPushButton::clicked,this,&LoginWindow::requestRegister);

}

void LoginWindow::paintEvent(QPaintEvent *)
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
    painter.drawPixmap(260,17,loginPic.width() - 15,loginPic.height() - 15,loginPic);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loginAccount()
{
    this->userName = this->ui->userNameEdit->text();
    this->password = this->ui->passwdEdit->text();
    emit this->userConfirmed();
}

void LoginWindow::registerAccount()
{
    this->userName = this->ui->userNameEdit->text();
    this->password = this->ui->passwdEdit->text();
    emit this->userRegistered();
}

void LoginWindow::back()
{
    this->ui->registerButton->setText("注册");
    this->ui->labelLogin->setText("LOGIN");
    this->ui->loginButton->setText("登录");
    this->setWindowTitle("登录");


    // 取消确定注册的按钮点击
    disconnect(this->ui->loginButton,&QPushButton::clicked,this,&LoginWindow::registerAccount);
    //取消返回按钮的点击
    disconnect(this->ui->registerButton,&QPushButton::clicked,this,&LoginWindow::back);
    //监听登录按钮连接
    connect(this->ui->loginButton,&QPushButton::clicked,this,&LoginWindow::loginAccount);
    //监听请求注册按钮的连接
    connect(this->ui->registerButton,&QPushButton::clicked,this,&LoginWindow::requestRegister);

}

void LoginWindow::requestRegister()
{
    this->ui->registerButton->setText("返回");
    this->ui->labelLogin->setText("REGISTER");
    this->ui->loginButton->setText("注册");
    this->setWindowTitle("注册");

    //取消登录按钮连接
    disconnect(this->ui->loginButton,&QPushButton::clicked,this,&LoginWindow::loginAccount);
    //取消请求注册按钮的连接
    disconnect(this->ui->registerButton,&QPushButton::clicked,this,&LoginWindow::requestRegister);
    // 监听确定注册的按钮点击
    connect(this->ui->loginButton,&QPushButton::clicked,this,&LoginWindow::registerAccount);
    //监听返回按钮的点击
    connect(this->ui->registerButton,&QPushButton::clicked,this,&LoginWindow::back);
}

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDebug>
#include "config.h"
#include "user.h"

//----------------------------------构造析构--------------------------------------------

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->setWindowModality(Qt::WindowModal); // 设置为模态窗口
    //this->setAttribute(Qt::WA_DeleteOnClose);

    this->setFixedSize(517, 363);

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
    //this->setWindowFlags(Qt::WindowStaysOnTopHint);

    // 密码可见按钮
    QAction *toggleAction = new QAction(this);
    toggleAction->setIcon(QIcon(":/icon/closeEye.png")); // 默认闭眼图标
    toggleAction->setCheckable(true); // 允许切换状态

    // 将 QAction 添加到 QLineEdit 的右侧
    ui->passwdEdit->addAction(toggleAction, QLineEdit::TrailingPosition);

    // 连接信号槽：点击时切换密码可见性
    connect(toggleAction, &QAction::toggled, [this, toggleAction](bool checked)
    {
        ui->passwdEdit->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
        toggleAction->setIcon(checked ? QIcon(":/icon/openEye.png") : QIcon(":/icon/closeEye.png"));
    });

    // 登录 按钮的点击
    connect(this->ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginAccount);

    //请求注册 按钮的点击
    connect(this->ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRequestRegister);

    //检测密码长度
    connect(ui->passwdEdit, &QLineEdit::textChanged, this, &LoginWindow::checkPasswordLength);

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

//----------------------------------公共方法--------------------------------------------

QString LoginWindow::getUserName()
{
    return this->m_userName;
}

QString LoginWindow::getUserPassword()
{
    return this->m_password;
}

//----------------------------------保护方法--------------------------------------------

void LoginWindow::paintEvent(QPaintEvent*)
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

//关闭事件
void LoginWindow::closeEvent(QCloseEvent*)
{
    emit this->userClose();
}

void LoginWindow::checkPasswordLength(const QString &password)
{
    const int currentLength = password.length();
    const int PASSWORD_MAX_LENGTH = User::pwdMaxLen;
    const int PASSWORD_MIN_LENGTH = User::pwdMinLen;

    // 判断长度是否超限
    if (currentLength > PASSWORD_MAX_LENGTH || currentLength < PASSWORD_MIN_LENGTH)
    {
        // 在checkPasswordLength函数中添加
        // 设置背景色+红色边框（保留原有透明度背景）
        this->ui->passwdEdit->setStyleSheet(
            "QLineEdit {"
            "   background-color: rgba(255, 255, 255, 100);"  // 保持原始背景
            "   border: 2px solid red;"                       // 新增红色边框
            "}"
        );

        // 显示红色警告
        // ui->lengthWarningLabel->setText(QString("密码过长（最多%1位）").arg(PASSWORD_MAX_LENGTH));
        // ui->lengthWarningLabel->setStyleSheet("color: red; font-size: 12px;");
        // ui->lengthWarningLabel->show();
    }
    else
    {
        this->ui->passwdEdit->setStyleSheet("background-color: rgba(255, 255, 255, 100);");
        // 隐藏提示或显示确认信息
        //ui->lengthWarningLabel->hide();
        // 显示绿色确认提示
        // ui->lengthWarningLabel->setText("✓ 长度符合要求");
        // ui->lengthWarningLabel->setStyleSheet("color: green;");
    }
}

//----------------------------------私有槽--------------------------------------------

//用户确定登录
void LoginWindow::onLoginAccount()
{
    this->m_userName = this->ui->userNameEdit->text();
    this->m_password = this->ui->passwdEdit->text();
    emit this->userConfirmed();
}

//用户确定注册
void LoginWindow::onRegisterAccount()
{
    this->m_userName = this->ui->userNameEdit->text();
    this->m_password = this->ui->passwdEdit->text();
    emit this->userRegistered();
}

//用户点击返回按钮
void LoginWindow::onBack()
{
    this->ui->registerButton->setText("注册");
    this->ui->labelLogin->setText("LOGIN");
    this->ui->loginButton->setText("登录");
    this->setWindowTitle("登录");

    // 取消确定注册的按钮点击
    disconnect(this->ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onRegisterAccount);
    //取消返回按钮的点击
    disconnect(this->ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onBack);
    //监听登录按钮连接
    connect(this->ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginAccount);
    //监听请求注册按钮的连接
    connect(this->ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRequestRegister);
    //将密码显示方式改成密码模式
    this->ui->passwdEdit->setEchoMode(QLineEdit::Password);

}

//用户点击注册账号按钮
void LoginWindow::onRequestRegister()
{
    this->ui->registerButton->setText("返回");
    this->ui->labelLogin->setText("REGISTER");
    this->ui->loginButton->setText("注册");
    this->setWindowTitle("注册");

    //取消登录按钮连接
    disconnect(this->ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginAccount);
    //取消请求注册按钮的连接
    disconnect(this->ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onRequestRegister);
    // 监听确定注册的按钮点击
    connect(this->ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onRegisterAccount);
    //监听返回按钮的点击
    connect(this->ui->registerButton, &QPushButton::clicked, this, &LoginWindow::onBack);
    //将密码显示方式改成普通
    this->ui->passwdEdit->setEchoMode(QLineEdit::Normal);
}

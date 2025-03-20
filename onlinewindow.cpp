#include "onlinewindow.h"
#include "ui_onlinewindow.h"

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

}

OnlineWindow::~OnlineWindow()
{
    delete ui;
}

#include "mydialog.h"
#include "ui_mydialog.h"

myDialog::myDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    //设置关闭属性 防止内存泄露
    this->setAttribute(Qt::WA_DeleteOnClose);

    //点击确定按钮 获取 lineEdit 信息
    connect(this->ui->confirmButton,&QPushButton::clicked,this,&myDialog::confirmButtonClicked);
    connect(this->ui->confirmButton,&QPushButton::clicked,this,[=](){
        emit this->getedInfo();
        this->close();
    });

    //点击取消按钮 关闭窗口
    connect(this->ui->cancelButton,&QPushButton::clicked,this,[=](){
        this->close();
    });


}

myDialog::~myDialog()
{
    delete ui;
}

int myDialog::getNum1()
{
    return this->m_num1;
}

int myDialog::getNum2()
{
    return this->m_num2;
}

int myDialog::getNum3()
{
    return this->m_num3;
}

int myDialog::getNum4()
{
    return this->m_num4;
}

int myDialog::getNum5()
{
    return this->m_num5;
}

//槽函数
void myDialog::confirmButtonClicked()
{
    QString str = ui->lineEdit1->text();


    bool ok = true;
    int number = str.toInt(&ok);

    //获取关卡数
    if (ok && number>0 && number<=37)
    {
        m_num1 = number;
    }
    else
    {
        QMessageBox::warning(this, "警告", "无效的输入");
        return;
    }

    //获取步数
    str = ui->lineEdit2->text();
    number = str.toInt(&ok);
    if (ok && number >= 0 && number <= 1000)
    {
        m_num2 = number;
    }
    else
    {
        QMessageBox::warning(this, "警告", "无效的输入");
        return;

    }

    //获取行数
    str = ui->lineEdit3->text();
    number = str.toInt(&ok);
    if (ok && number > 0 && number <= 20)
    {
        m_num3 = number - 1;
    }
    else
    {
        QMessageBox::warning(this, "警告", "无效的输入");
        return;

    }

    //获取列数
    str = ui->lineEdit4->text();
    number = str.toInt(&ok);
    if (ok && number > 0 && number <= 20)
    {
        m_num4 = number - 1;
    }
    else
    {
        QMessageBox::warning(this, "警告", "无效的输入");
        return;
    }

    //获取方向
    str = ui->lineEdit5->text();
    number = str.toInt(&ok);
    if (ok && number >= 0 && number <= 3)
    {
        m_num5 = number;
    }
    else
    {
       QMessageBox::warning(this, "警告", "无效的输入");
        return;
    }

}

#include "buildmapdialog.h"
#include "ui_buildmapdialog.h"

//----------------------------------构造析构--------------------------------------------

BuildMapDialog::BuildMapDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BuildMapDialog)
{
    ui->setupUi(this);
    setLineEditsStyle();

    this->setWindowTitle("自建地图");
    setBackground(":/image/musicBackgnd.png");

    //设置关闭属性 防止内存泄露
    //this->setAttribute(Qt::WA_DeleteOnClose);

    //点击确定按钮 获取 lineEdit 信息
    connect(this->ui->confirmButton, &QPushButton::clicked, this, &BuildMapDialog::onConfirmButtonClicked);

    //点击取消按钮 关闭窗口
    connect(this->ui->cancelButton, &QPushButton::clicked, this, &QDialog::close);

}

BuildMapDialog::~BuildMapDialog()
{
    delete ui;
}

//----------------------------------公有方法--------------------------------------------

int BuildMapDialog::getNum1()
{
    return this->m_num1;
}

int BuildMapDialog::getNum2()
{
    return this->m_num2;
}

int BuildMapDialog::getNum3()
{
    return this->m_num3;
}

int BuildMapDialog::getNum4()
{
    return this->m_num4;
}

int BuildMapDialog::getNum5()
{
    return this->m_num5;
}

void BuildMapDialog::setBackground(const QString fileName)
{
    QPixmap pix(fileName);
    QSize windowSize = this->size();
    QPixmap scalePix = pix.scaled(windowSize);

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window, QBrush(scalePix));

    this->setPalette(palette);
}

void BuildMapDialog::setLineEditStyle(QLineEdit *le)
{
    le->setStyleSheet("QLineEdit {"
                      "background-color: rgba(255,255,255,0.2);"
                      "}");
}

void BuildMapDialog::setLineEditsStyle()
{
    QList<QLineEdit*> lineEdits = this->findChildren<QLineEdit*>();

    // 遍历所有 QLineEdit
    for (QLineEdit *lineEdit : lineEdits)
    {
        setLineEditStyle(lineEdit);
    }
}

//----------------------------------私有槽--------------------------------------------

//用户点击确定按钮
void BuildMapDialog::onConfirmButtonClicked()
{
    QString str = ui->lineEdit1->text();

    bool ok = true;
    int number = str.toInt(&ok);

    //获取关卡数
    if (ok && number > 0 && number <= 37)
    {
        m_num1 = number;
    }
    else
    {
        QMessageBox::warning(this, "警告", "关卡数为无效输入");
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
        QMessageBox::warning(this, "警告", "步数为无效输入");
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
        QMessageBox::warning(this, "警告", "bug所在行数为无效输入");
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
        QMessageBox::warning(this, "警告", "bug所在列数为无效输入");
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
        QMessageBox::warning(this, "警告", "bug方向为无效输入");
        return;
    }

    //信息正确
    emit this->getedInfo();
    this->hide();
}

#include "mypushbutton.h"
#include "config.h"

//----------------------------------静态方法--------------------------------------------

//创建按钮
MyPushButton* MyPushButton::createButton(Type type, QString text, QWidget* parent)
{
    MyPushButton* btn = new MyPushButton(text, parent);
    btn->setStyle(type);
    return btn;
}

//构造函数
MyPushButton::MyPushButton(QString text, QWidget* parent = nullptr) : QPushButton(parent)
{
    this->setText(text);
}

//设置形式
void MyPushButton::setStyle(Type type)
{
    switch(type)
    {
        case commonButton:
        {
            this->setFont(QFont("华文新魏", 15));
            this->setFixedSize(120, 50);
            break;
        }

        case tipButton:
        {
            QPixmap pix = QPixmap(TIPPATH);
            this->setFixedSize(35, 35);
            this->setIconSize(pix.size());
            this->setIcon(QIcon(pix));
            this->setStyleSheet("QPushButton{border:0px}");  //设置不规则图形
            break;
        }
    }
}

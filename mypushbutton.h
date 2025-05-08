#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
public:

    enum Type
    {
        commonButton,
        tipButton
    };

    //创建按钮
    static MyPushButton* createButton(Type type, QString text = "", QWidget* parent = nullptr);

private:

    //构造函数
    MyPushButton(QString text, QWidget* parent);

    //设置按钮形式
    void setStyle(Type type);
};

#endif // MYPUSHBUTTON_H

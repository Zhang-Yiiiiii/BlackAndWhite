#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

/*****************************************************************
 * class: MyPushButton （自定义按钮）
 *
 * 用处: 统一按钮风格
 *
 *****************************************************************/

#include <QPushButton>

class MyPushButton : public QPushButton
{
public:
    //------------------------公共类型----------------------------------

    enum Type
    {
        commonButton,
        tipButton
    };

    //------------------------静态方法----------------------------------

    //创建按钮
    static MyPushButton* createButton(Type type, QString text = "", QWidget* parent = nullptr);

private:
    //------------------------私有方法----------------------------------

    //构造函数
    MyPushButton(QString text, QWidget* parent);

    //设置按钮形式
    void setStyle(Type type);
};

#endif // MYPUSHBUTTON_H

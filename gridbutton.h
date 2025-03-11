#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include "config.h"
#include <QWidget>
#include <QPushButton>
#include <QPixmap>

class GridButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GridButton(bool flag, QWidget *parent = nullptr);

    //加载图片
    QPixmap pix;


    //标志正反
    bool flag = true;   //true 表示格子为白色 false表示格子为黑色
    //改变正反
    void changeFlag();

    //格子标号
    int posx;
    int posy;

signals:
};

#endif // GRIDBUTTON_H

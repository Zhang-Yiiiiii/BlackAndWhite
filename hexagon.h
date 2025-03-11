#ifndef HEXAGON_H
#define HEXAGON_H

#include "config.h"
#include <QWidget>
#include <QMainWindow>
#include <QIcon>
#include <QFont>
#include <QPoint>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QRect>


class Hexagon : public QPushButton
{
    Q_OBJECT
public:
    Hexagon(int id ,QPushButton * parent = nullptr);

    //按钮图片
    QPixmap pix;

    //按钮序号
    int id = 0;

    //重写绘图函数
    void paintEvent(QPaintEvent *event) override;



signals:

    //被点击时告诉主场景
    void beClicked(int gameLevel);
};

#endif // HEXAGON_H

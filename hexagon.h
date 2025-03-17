#ifndef HEXAGON_H
#define HEXAGON_H

/*
 * class: Hexagon （六边形）
 *
 * 用处: 作为主界面的选关按钮、传递被点击时的关卡数
 */

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
    QPixmap m_pix;

    //按钮序号
    int m_id = 0;

    //重写绘图函数
    void paintEvent(QPaintEvent *event) override;

signals:

    //被点击时告诉主场景
    void beClicked(int gameLevel);
};

#endif // HEXAGON_H

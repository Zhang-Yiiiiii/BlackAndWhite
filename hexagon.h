#ifndef HEXAGON_H
#define HEXAGON_H

/*****************************************************************
 * class: Hexagon （六边形）
 *
 * 用处: 作为主界面的选关按钮、传递被点击时的关卡数
 *****************************************************************/

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
#include <QMouseEvent>
#include <QPainterPath>
#include <QGraphicsEffect>
#include <QGraphicsScale>

class Hexagon : public QPushButton
{
    Q_OBJECT
public:
    //------------------------构造析构----------------------------------

    Hexagon(int id, QPushButton * parent = nullptr);

    //------------------------公有方法----------------------------------

    //设置序号
    Hexagon* setId(int id);

    //获取序号
    int getId() const;

    //获取边长
    static int getSideLength();

protected:
    //重写绘图函数
    void paintEvent(QPaintEvent *event) override;

private:

    //------------------------私有属性----------------------------------

    //按钮序号
    int m_id = 0;

    //边长
    const static int sideLength = 48;

    QColor m_fillColor = Qt::white;
    QColor m_textColor = Qt::black;

    // 背景图（只加载一次）
    QPixmap backgroundPixmap = QPixmap(":/image/newbackground.png");

    // QColor m_backgroundColor = Qt::white; // 采样到的背景颜色
    // QColor m_fillColor = Qt::white;       // 填充颜色（反色）
    // QColor m_textColor = Qt::black;       // 文字颜色（反色）

    // // 获取背景颜色的亮度（0~255）
    // int getBackgroundLuminance() const;

    // // 判断颜色是否偏亮（亮度阈值可调）
    // bool isLightBackground() const;

    void sampleBackgroundColor();   //采样背景颜色

signals:

    //------------------------信号----------------------------------

    //被点击时告诉主场景
    void beClicked(int gameLevel);
};

#endif // HEXAGON_H

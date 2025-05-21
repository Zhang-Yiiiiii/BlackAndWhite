#include "hexagon.h"

//----------------------------------构造析构--------------------------------------------

Hexagon::Hexagon(int id, QPushButton * parent):
    QPushButton(parent), m_id(id + 1)
{
    //设置按钮大小
    this->setFixedSize(110, 110);

    setAttribute(Qt::WA_TranslucentBackground); // 关键：启用透明背景

    //设置边框为不规则
    //this->setStyleSheet("QPushButton{border:0px}");

    //设置按钮的数字
    this->setText(QString::number(this->m_id));

    //告诉主场景被点击
    connect(this, &QPushButton::clicked, this, [ = ]()
    {
        emit beClicked(this->m_id);
    });
}

//----------------------------------公有方法--------------------------------------------

Hexagon* Hexagon::setId(int id)
{
    m_id = id;
    return this;
}

int Hexagon::getId() const
{
    return m_id;
}

int Hexagon::getSideLength()
{
    return sideLength;
}

// void Hexagon::paintEvent(QPaintEvent *event)
// {
// Q_UNUSED(event);
// QPainter painter(this);
// painter.setRenderHint(QPainter::Antialiasing);
// painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 启用平滑变换 （没设置之前有毛边)

//     // 计算六边形顶点（中心+半径）
// QRect rect = contentsRect();
// const int radius = sideLength;
// QPointF center = rect.center();
// QVector<QPointF> points;

// for (int i = 0; i < 6; ++i)
// {
// double angle = (i * 60.0 - 30.0) * M_PI / 180.0;
// points << QPointF(center.x() + radius * cos(angle),
// center.y() + radius * sin(angle));
// }

//     // 创建带圆角的六边形路径（使用贝塞尔曲线）
// QPainterPath path;
// const qreal roundness = 100.0; // 圆角强度，值越大越圆润

// for (int i = 0; i < 6; ++i)
// {
// QPointF p1 = points[i];
// QPointF p2 = points[(i + 1) % 6];
// QPointF mid = (p1 + p2) / 2;

// if (i == 0)
// {
// path.moveTo(p1);
// }

//         // 绘制贝塞尔曲线模拟圆角
// QPointF c1 = p1 + (mid - p1) * roundness / 100;
// QPointF c2 = mid + (p2 - mid) * roundness / 100;
// path.cubicTo(c1, c2, p2);
// }

// path.closeSubpath();
//     // 设置加粗的圆角边框
// QPen pen(Qt::white, 4.0); // 边框宽度=4px，颜色白色
// pen.setJoinStyle(Qt::RoundJoin); // 圆角连接
// painter.setPen(pen);
// painter.setBrush(Qt::NoBrush); // 透明填充
// painter.drawPath(path);
//     // 设置遮罩（确保点击区域匹配）
// setMask(QRegion(path.toFillPolygon().toPolygon()));
//     // 绘制文本
// painter.setPen(Qt::black);
// painter.drawText(rect, Qt::AlignCenter, text());
// }

//重写绘图事件
void Hexagon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 启用平滑变换 （没设置之前有毛边)

    // 创建一个六边形的 QPainterPath
    QPainterPath hexagonPath;
    QRect rect = contentsRect();//重写绘图事件

    const int radius = Hexagon::sideLength ;  // 六边形的外接圆半径

    // 计算六边形的顶点
    QPointF center(rect.center());

    for (int i = 0; i < 6; ++i)
    {
        double angle = (i * 60.0 - 30.0) * M_PI / 180.0; // 每个顶点的角度
        QPointF point(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));

        if (i == 0)
        {
            hexagonPath.moveTo(point); // 移动到第一个顶点
        }
        else
        {
            hexagonPath.lineTo(point); // 连接到其他顶点
        }
    }

    hexagonPath.closeSubpath(); // 闭合路径

    // 设置画笔和画刷
    painter.setBrush(Qt::white);
    QPen pen(Qt::NoPen);
    painter.setPen(pen);
    painter.drawPath(hexagonPath);

    // 绘制按钮文本
    QFont font("华文新魏", 15);
    font.setBold(true);

    painter.setFont(font);
    painter.setPen(QPen(Qt::black));
    painter.drawText(rect, Qt::AlignCenter, text());

    // 将 QPainterPath 转换为 QRegion
    QRegion hexagonRegion(hexagonPath.toFillPolygon().toPolygon());
    this->setMask(hexagonRegion); // 设置按钮的遮罩
}

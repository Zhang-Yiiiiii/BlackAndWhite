#include "hexagon.h"

//----------------------------------构造析构--------------------------------------------

Hexagon::Hexagon(int id, QPushButton * parent):
    QPushButton(parent), m_id(id + 1)
{
    //设置按钮大小
    this->setFixedSize(110, 110);

    //设置边框为不规则
    this->setStyleSheet("QPushButton{border:0px}");

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

//重写绘图事件
void Hexagon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 启用平滑变换 （没设置之前有毛边)

    // 创建一个六边形的 QPainterPath
    QPainterPath hexagonPath;
    QRect rect = contentsRect();
    const int sideLength = Hexagon::sideLength; // 六边形的边长
    const int radius = sideLength ;  // 六边形的外接圆半径

    // 计算六边形的顶点
    QPointF center(rect.center());

    for (int i = 0; i < 6; ++i)
    {
        double angle = (i * 60.0 - 30.0) * M_PI / 180.0; // 每个顶点的角度
        QPointF point(center.x() + radius * cos(angle), center.y() + radius * sin(angle));

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
    painter.setBrush(Qt::black);
    painter.setPen(Qt::white);
    painter.drawPath(hexagonPath);

    // 绘制按钮文本
    QFont font("华文新魏", 15);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter, text());

    // 将 QPainterPath 转换为 QRegion
    QRegion hexagonRegion(hexagonPath.toFillPolygon().toPolygon());
    this->setMask(hexagonRegion); // 设置按钮的遮罩
}

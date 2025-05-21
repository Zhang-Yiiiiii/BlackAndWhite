#include "hexagon.h"
#include <QTimer>

//----------------------------------构造析构--------------------------------------------

// Hexagon::Hexagon(int id, QPushButton * parent):
// QPushButton(parent), m_id(id + 1)
// {
//     //设置按钮大小
// this->setFixedSize(110, 110);

// setAttribute(Qt::WA_TranslucentBackground); // 关键：启用透明背景

//     //设置边框为不规则
//     //this->setStyleSheet("QPushButton{border:0px}");

//     //设置按钮的数字
// this->setText(QString::number(this->m_id));

//     //告诉主场景被点击
// connect(this, &QPushButton::clicked, this, [ = ]()
// {
// emit beClicked(this->m_id);
// });
// }

Hexagon::Hexagon(int id, QPushButton *parent)
    : QPushButton(parent), m_id(id + 1)
{
    this->setFixedSize(110, 110);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setText(QString::number(this->m_id));

    // ⏳ 延迟采样：等事件队列空闲时再执行（动画后）
    QTimer::singleShot(2000, this, &Hexagon::sampleBackgroundColor);

    // 通知主窗口点击事件
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

// //重写绘图事件    //原画图
// void Hexagon::paintEvent(QPaintEvent *event)
// {
// Q_UNUSED(event)

// QPainter painter(this);
// painter.setRenderHint(QPainter::Antialiasing, true);
// painter.setRenderHint(QPainter::SmoothPixmapTransform, true); // 启用平滑变换 （没设置之前有毛边)

//     // 创建一个六边形的 QPainterPath
// QPainterPath hexagonPath;
// QRect rect = contentsRect();//重写绘图事件

// const int radius = Hexagon::sideLength ;  // 六边形的外接圆半径

//     // 计算六边形的顶点
// QPointF center(rect.center());

// for (int i = 0; i < 6; ++i)
// {
// double angle = (i * 60.0 - 30.0) * M_PI / 180.0; // 每个顶点的角度
// QPointF point(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));

// if (i == 0)
// {
// hexagonPath.moveTo(point); // 移动到第一个顶点
// }
// else
// {
// hexagonPath.lineTo(point); // 连接到其他顶点
// }
// }

// hexagonPath.closeSubpath(); // 闭合路径

//     // 设置画笔和画刷
// painter.setBrush(Qt::white);
// QPen pen(Qt::NoPen);
// painter.setPen(pen);
// painter.drawPath(hexagonPath);

//     // 绘制按钮文本
// QFont font("华文新魏", 15);
// font.setBold(true);

// painter.setFont(font);
// painter.setPen(QPen(Qt::black));
// painter.drawText(rect, Qt::AlignCenter, text());

//     // 将 QPainterPath 转换为 QRegion
// QRegion hexagonRegion(hexagonPath.toFillPolygon().toPolygon());
// this->setMask(hexagonRegion); // 设置按钮的遮罩
// }

// //根据中心着色
// void Hexagon::paintEvent(QPaintEvent *event)
// {
// Q_UNUSED(event)

//     // -------- 采样背景颜色 --------
// sampleBackgroundColor();

// QPainter painter(this);
// painter.setRenderHint(QPainter::Antialiasing, true);
// painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

//     // 创建六边形路径
// QPainterPath hexagonPath;
// QRect rect = contentsRect();
// const int radius = Hexagon::getSideLength();
// QPointF center(rect.center());

// for (int i = 0; i < 6; ++i)
// {
// double angle = (i * 60.0 - 30.0) * M_PI / 180.0;
// QPointF point(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));

// if (i == 0)
// {
// hexagonPath.moveTo(point);
// }
// else
// {
// hexagonPath.lineTo(point);
// }
// }

// hexagonPath.closeSubpath();

//     // 设置画笔和画刷
// painter.setBrush(m_fillColor);
// painter.setPen(Qt::NoPen);
// painter.drawPath(hexagonPath);

//     // 设置遮罩（六边形形状）
// QRegion hexRegion(hexagonPath.toFillPolygon().toPolygon());
// setMask(hexRegion);

//     // 绘制文本
// QFont font("华文新魏", 15);
// font.setBold(true);
// painter.setFont(font);
// painter.setPen(m_textColor);
// painter.drawText(rect, Qt::AlignCenter, text());
// }

//逐像素着色
void Hexagon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QRect rect = this->rect();
    QPointF center = rect.center();
    const int radius = Hexagon::sideLength;

    // 构造六边形路径
    QPainterPath hexPath;

    for (int i = 0; i < 6; ++i)
    {
        double angle = (i * 60.0 - 30.0) * M_PI / 180.0;
        QPointF pt(center.x() + radius * qCos(angle), center.y() + radius * qSin(angle));

        if (i == 0)
        {
            hexPath.moveTo(pt);
        }
        else
        {
            hexPath.lineTo(pt);
        }
    }

    hexPath.closeSubpath();

    // 创建遮罩
    QRegion hexRegion(hexPath.toFillPolygon().toPolygon());
    this->setMask(hexRegion);

    // 准备背景图片（仅一次加载）
    static QImage backgroundImage;
    static bool loaded = false;

    if (!loaded)
    {
        backgroundImage.load(":/image/newbackground.png"); // 用你的实际路径
        loaded = true;
    }

    // 遍历六边形区域内像素，分区域采样背景亮度，逐像素着色
    QImage buffer(rect.size(), QImage::Format_ARGB32_Premultiplied);
    buffer.fill(Qt::transparent);

    QPainter bufPainter(&buffer);

    for (int y = 0; y < rect.height(); y += 1)
    {
        for (int x = 0; x < rect.width(); x += 1)
        {
            QPoint localPt(x, y);

            if (!hexPath.contains(localPt))
            {
                continue;
            }

            QPoint globalPos = this->mapToGlobal(localPt);
            QWidget* topWidget = this->window();
            QPoint bgPos = topWidget->mapFromGlobal(globalPos);

            QColor bgColor = Qt::white;

            if (!backgroundImage.isNull() &&
                backgroundImage.rect().contains(bgPos))
            {
                bgColor = backgroundImage.pixelColor(bgPos);
            }

            QColor fillColor = (bgColor.lightness() < 128) ? Qt::white : Qt::black;
            buffer.setPixelColor(x, y, fillColor);
        }
    }

    // 把像素图绘制到按钮上
    painter.drawImage(0, 0, buffer);

    // 绘制文本（居中）
    QFont font("华文新魏", 15);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(Qt::red); // 或自动反色处理

    painter.drawText(rect, Qt::AlignCenter, this->text());
}

void Hexagon::sampleBackgroundColor()
{
    if (backgroundPixmap.isNull())
    {
        return;
    }

    // 获取按钮在主窗口的全局坐标
    QPoint globalPos = this->mapToGlobal(QPoint(0, 0));
    QWidget* topWidget = this->window(); // 主窗口
    QPoint topLeft = topWidget->mapFromGlobal(globalPos);

    QRect sampleRect(topLeft, this->size());
    QImage bgImg = backgroundPixmap.toImage();

    long r = 0, g = 0, b = 0, count = 0;

    for (int y = 0; y < sampleRect.height(); ++y)
    {
        for (int x = 0; x < sampleRect.width(); ++x)
        {
            int imgX = sampleRect.left() + x;
            int imgY = sampleRect.top() + y;

            if (imgX >= 0 && imgX < bgImg.width() && imgY >= 0 && imgY < bgImg.height())
            {
                QColor pixel = bgImg.pixelColor(imgX, imgY);
                r += pixel.red();
                g += pixel.green();
                b += pixel.blue();
                ++count;
            }
        }
    }

    if (count > 0)
    {
        QColor avgColor(r / count, g / count, b / count);
        m_fillColor = (avgColor.lightness() < 128) ? Qt::white : Qt::black;
        m_textColor = (avgColor.lightness() < 128) ? Qt::black : Qt::white;
    }

    update();
}

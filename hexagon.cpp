#include "hexagon.h"
#include <QTimer>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

//----------------------------------构造析构--------------------------------------------

Hexagon::Hexagon(int id, QPushButton *parent)
    : QPushButton(parent), m_id(id + 1)
{
    this->setFixedSize(110, 110);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setCursor(Qt::PointingHandCursor);
    this->setText(QString::number(this->m_id));

    // 延迟采样：等事件队列空闲时再执行（动画后）
    QTimer::singleShot(2000, this, &Hexagon::sampleBackgroundColor);

    // 通知主窗口点击事件
    connect(this, &QPushButton::clicked, this, [ = ]()
    {
        emit beClicked(this->m_id);
    });

    hoverAnim = new QSequentialAnimationGroup(this);

    // 初始位置先不设置，等 enterEvent 中记录
    connect(hoverAnim, &QSequentialAnimationGroup::finished, this, [ = ]()
    {
        animRunning = false;
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
        backgroundImage.load(BACKGROUDPATH);
        loaded = true;
    }

    // 遍历六边形区域内像素，分区域采样背景亮度，逐像素着色
    QImage buffer(rect.size(), QImage::Format_ARGB32_Premultiplied);
    buffer.fill(Qt::transparent);

    QPainter bufPainter(&buffer);
    QPoint centerPt = rect.center(); // 中心点坐标
    QColor centerColor; // 用于存储中心点颜色

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

            // 记录中心点颜色
            if (x == centerPt.x() && y == centerPt.y())
            {
                centerColor = fillColor;
            }
        }
    }

    // 把像素图绘制到按钮上
    painter.drawImage(0, 0, buffer);

    if (centerColor.isValid())
    {
        // 方法1：直接RGB反色（适用于纯黑/纯白）
        m_textColor = QColor(255 - centerColor.red(),
                             255 - centerColor.green(),
                             255 - centerColor.blue());
    }
    else
    {
        m_textColor = Qt::red; // 备用颜色
    }

    //绘制文本（居中）
    QFont font("华文新魏", 15);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(m_textColor); // 或自动反色处理

    painter.drawText(rect, Qt::AlignCenter, this->text());
}

void Hexagon::enterEvent(QEnterEvent *event)
{
    if (animRunning)
    {
        return;    // 防止重复触发
    }

    originalPos = pos();
    animRunning = true;

    // 清除旧动画
    hoverAnim->clear();

    // 向上移动动画
    QPropertyAnimation *up = new QPropertyAnimation(this, "pos");
    up->setDuration(300);
    up->setStartValue(originalPos);
    up->setEndValue(originalPos - QPoint(0, 5));
    up->setEasingCurve(QEasingCurve::OutCubic);

    // 回弹动画
    QPropertyAnimation *down = new QPropertyAnimation(this, "pos");
    down->setDuration(100);
    down->setStartValue(originalPos - QPoint(0, 5));
    down->setEndValue(originalPos);
    down->setEasingCurve(QEasingCurve::InCubic);

    hoverAnim->addAnimation(up);
    hoverAnim->addAnimation(down);
    hoverAnim->start();

    QPushButton::enterEvent(event);
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

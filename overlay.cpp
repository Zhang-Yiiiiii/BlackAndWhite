#include "overlay.h"

#include <QPainter>
#include <QPainterPath>

QColor Overlay::m_lineColor = Qt::red; // 默认红色路径
int Overlay::m_lineWidth = 2;          // 默认线宽
int Overlay::m_pointRadius = 3;        // 默认点半径

Overlay::Overlay(QWidget *parent)
    : QWidget(parent)
{
    // 基础属性设置
    setAttribute(Qt::WA_TransparentForMouseEvents); // 鼠标穿透
    setAttribute(Qt::WA_TranslucentBackground);     // 透明背景
    setStyleSheet("background: transparent;");      // 确保透明
}

void Overlay::setPath(const QVector<QPoint>& pixelPath)
{
    m_pixelPath = pixelPath;
    update(); // 触发重绘
}

void Overlay::setLineColor(const QColor& color)
{
    m_lineColor = color;
    update();
}

void Overlay::setLineWidth(int width)
{
    m_lineWidth = width;
    update();
}

void Overlay::setPointRadius(int radius)
{
    m_pointRadius = radius;
    update();
}

void Overlay::clearPath()
{
    m_pixelPath.clear();
    update();
}

void Overlay::setPathColor(const QColor& color)
{
    if (m_lineColor != color)
    {
        m_lineColor = color;
        update(); // 颜色变化时触发重绘
    }
}

void Overlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_pixelPath.isEmpty())
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制路径线
    painter.setPen(QPen(m_lineColor, m_lineWidth));

    for (int i = 1; i < m_pixelPath.size(); ++i)
    {
        painter.drawLine(m_pixelPath[i - 1], m_pixelPath[i]);
    }

    // 绘制路径点
    painter.setBrush(m_lineColor);

    for (const auto& pt : m_pixelPath)
    {
        painter.drawEllipse(pt, m_pointRadius, m_pointRadius);
    }
}

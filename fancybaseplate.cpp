#include "FancyBasePlate.h"
#include <QPainter>
#include <QPainterPath>

FancyBasePlate::FancyBasePlate(QWidget* parent, const QPoint& pos, int rows, int cols, const QColor& color)
    : QWidget(parent), m_rows(rows), m_cols(cols), m_baseColor(color)
{
    setAttribute(Qt::WA_TranslucentBackground); // 启用半透明支持
    move(pos.x() - PADDING, pos.y() - PADDING);
    resize(calculateTotalSize());

    // 初始化高光色
    m_highlightColor = QColor(255, 255, 255, 60);
    // 启用悬浮跟踪
    setAttribute(Qt::WA_Hover);
}

void FancyBasePlate::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const QSize totalSize = calculateTotalSize();
    const int radius = 8;  // 圆角半径
    // ===== 1. 背景渐变 =====
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0.0, m_baseColor.lighter(110));
    gradient.setColorAt(0.5, m_baseColor);
    gradient.setColorAt(1.0, m_baseColor.darker(110));
    // ===== 2. 带圆角的主体 =====
    QPainterPath backgroundPath;
    backgroundPath.addRoundedRect(0, 0, totalSize.width(), totalSize.height(), radius, radius);
    // 绘制渐变背景
    painter.fillPath(backgroundPath, gradient);
    // ===== 3. 内发光效果 =====
    painter.setPen(QPen(m_highlightColor, 1.5));
    painter.drawPath(backgroundPath);

    // ===== 4. 悬浮高光 =====
    if (m_hovered)
    {
        QPainterPath hoverPath;
        hoverPath.addRoundedRect(1, 1,
                                 totalSize.width() - 2,
                                 totalSize.height() - 2,
                                 radius - 1, radius - 1);
        painter.fillPath(hoverPath, QBrush(QColor(255, 255, 255, 20)));
    }

    // ===== 5. 细节装饰线 =====
    painter.setPen(QPen(m_baseColor.darker(130), 0.5));
    painter.drawRoundedRect(0, 0, totalSize.width(), totalSize.height(), radius, radius);
}

// ===== 悬浮效果支持 =====
void FancyBasePlate::enterEvent(QEnterEvent* event)
{
    m_hovered = true;
    update();
    QWidget::enterEvent(event);
}

void FancyBasePlate::leaveEvent(QEvent* event)
{
    m_hovered = false;
    update();
    QWidget::leaveEvent(event);
}

void FancyBasePlate::setHighlightColor(const QColor& color)
{
    m_highlightColor = color;
    update();
}

QSize FancyBasePlate::calculateTotalSize() const
{
    // 总尺寸 = 两侧扩展 + (格子尺寸 * 列数) + (间隙 * (列数 - 1))
    int width = 2 * PADDING + m_cols * CELL_SIZE + (m_cols - 1) * GAP;
    int height = 2 * PADDING + m_rows * CELL_SIZE + (m_rows - 1) * GAP;
    return QSize(width, height);
}

void FancyBasePlate::setGridSize(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
    resize(calculateTotalSize());
    update();
}

void FancyBasePlate::setBaseColor(const QColor& color)
{
    m_baseColor = color;
    update();
}

// void FancyBasePlate::paintEvent(QPaintEvent* event)
// {
// Q_UNUSED(event)
// QPainter painter(this);
// painter.setRenderHint(QPainter::Antialiasing);

// painter.fillRect(0, 0, calculateTotalSize().width(), calculateTotalSize().height(), m_baseColor);
// }

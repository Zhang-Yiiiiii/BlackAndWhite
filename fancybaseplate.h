#ifndef FANCYBASEPLATE_H
#define FANCYBASEPLATE_H

#include <QWidget>
#include <QColor>
#include <QGraphicsDropShadowEffect>

class FancyBasePlate : public QWidget
{
    Q_OBJECT
public:
    explicit FancyBasePlate(
        QWidget* parent = nullptr,
        const QPoint& pos = QPoint(0, 0),
        int rows = 8,
        int cols = 8,
        const QColor& color = QColor(200, 200, 200, 150) // 默认半透明白色
    );

    void setGridSize(int rows, int cols);
    void setBaseColor(const QColor& color);
    void setHighlightColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void enterEvent(QEnterEvent* event) override;

private:
    int m_rows;
    int m_cols;
    QColor m_baseColor;
    const int CELL_SIZE = 35;    // 格子大小
    const int GAP = 1;           // 格子间隙
    const int PADDING = 6;       // 四周扩展（左、上、右、下各2px）

    // FancyBasePlate.h 新增成员
private:
    bool m_hovered = false;              // 悬浮状态
    QColor m_highlightColor;             // 高光色

    QSize calculateTotalSize() const;
};

#endif // FANCYBASEPLATE_H

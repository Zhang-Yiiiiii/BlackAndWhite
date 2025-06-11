#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QVector>
#include <QPoint>

/*****************************************************************
 * class: Overlay （覆盖层）
 *
 * 用处: 显示路径
 *
 *****************************************************************/

class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget *parent = nullptr);

    // 设置像素坐标路径（由父窗口转换后传入）
    void setPath(const QVector<QPoint>& pixelPath);

    // 可选样式设置方法
    void setLineColor(const QColor& color);
    void setLineWidth(int width);
    void setPointRadius(int radius);
    void clearPath();
    void setPathColor(const QColor& color); // 颜色设置方法

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPoint> m_pixelPath;  // 存储像素坐标路径
    static QColor m_lineColor; // 默认红色路径
    static int m_lineWidth;          // 默认线宽
    static int m_pointRadius;        // 默认点半径
};

#endif // OVERLAY_H

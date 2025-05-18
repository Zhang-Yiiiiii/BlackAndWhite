// gridbutton.cpp
#include "gridbutton.h"
#include "config.h"
#include <QPainter>
#include <QPropertyAnimation>

GridButton::GridButton(bool flag, QWidget *parent)
    : QPushButton(parent), m_flag(flag)
{
    m_frontPix.load(GRIDPATH1);  // 替换为实际路径
    m_backPix.load(GRIDPATH2);   // 替换为实际路径

    QSize maxSize(qMax(m_frontPix.width(), m_backPix.width()),
                  qMax(m_frontPix.height(), m_backPix.height()));
    setFixedSize(maxSize);

    setStyleSheet("background: transparent; border: none;");

    connect(this, &QPushButton::clicked, this, [ = ]()
    {
        if(!m_animating)
        {
            emit beClicked(m_posx, m_posy);
        }
    });
}

void GridButton::setRotationAngle(int angle)
{
    if (m_rotationAngle != angle)
    {
        m_rotationAngle = angle;
        update();
        emit rotationAngleChanged();
    }
}

void GridButton::changeFlag(bool isShowAnimation)
{
    if(m_animating)
    {
        return;
    }

    m_targetFlag = !m_flag;
    m_animating = true;

    QPropertyAnimation *anim = new QPropertyAnimation(this, "rotationAngle");
    anim->setDuration(400);

    if(!isShowAnimation)    //主要是在随机生成中，翻转太快导致无法翻转
    {
        anim->setDuration(0);
    }

    anim->setEasingCurve(QEasingCurve::InOutQuad);
    anim->setStartValue(0);
    anim->setEndValue(180);

    connect(anim, &QPropertyAnimation::finished, this, [ = ]()
    {
        m_flag = m_targetFlag;
        m_animating = false;
        setRotationAngle(0);
        anim->deleteLater();
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void GridButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QTransform transform;
    const QRect rect = this->rect();
    const QPoint center = rect.center();

    // 应用3D变换
    transform.translate(center.x(), center.y());
    transform.rotate(m_rotationAngle, Qt::YAxis);  // 使用Qt::YAxis
    transform.translate(-center.x(), -center.y());

    // 确定当前显示的图片
    QPixmap currentPix;

    if(m_rotationAngle <= 90)
    {
        currentPix = m_flag ? m_frontPix : m_backPix;
    }
    else
    {
        currentPix = m_targetFlag ? m_frontPix : m_backPix;
    }

    painter.setTransform(transform);
    painter.drawPixmap(rect, currentPix);
}

GridButton* GridButton::setPos(int posx, int posy)
{
    m_posx = posx;
    m_posy = posy;
    return this;
}

bool GridButton::getFlag() const
{
    return m_flag;
}

int GridButton::rotationAngle() const
{
    return m_rotationAngle;
}

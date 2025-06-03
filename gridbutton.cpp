#include "gridbutton.h"
#include "config.h"

#include <QPainter>
#include <QPropertyAnimation>

GridButton::GridButton(bool flag, QWidget *parent)
    : QPushButton(parent), m_flag(flag)
{
    setFixedSize(GRIDSIZE, GRIDSIZE);

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
    anim->setDuration(300);

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
    transform.rotate(m_rotationAngle, Qt::YAxis);
    transform.translate(-center.x(), -center.y());

    // 设置颜色而不是图片
    QColor currentColor;

    if(m_rotationAngle <= 90)
    {
        currentColor = m_flag ? Qt::white : Qt::black;
    }
    else
    {
        currentColor = m_targetFlag ? Qt::white : Qt::black;
    }

    painter.setTransform(transform);
    painter.fillRect(rect, currentColor);

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

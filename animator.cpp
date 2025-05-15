#include "animator.h"
#include<QPointer>

//----------------------------------静态方法--------------------------------------------

//创建对象
Animator* Animator::createAnimator(QWidget* target, AnimationType type, int duration)
{
    Animator* animator = new Animator(target);
    animator->setupAnimation(target, type, duration);
    return animator;
}

//过渡
void Animator::transition(QWidget* from, QWidget* to, int duration)
{

    // 先淡出
    Animator* fadeOut = Animator::createAnimator(from, FadeOut, duration);
    fadeOut->onFinished([from, to, duration]()
    {

        from->hide();

        // 再淡入
        Animator* fadeIn = Animator::createAnimator(to, FadeIn, duration);
        fadeIn->onFinished([to]()
        {
            // 清理特效
            //to->setGraphicsEffect(nullptr);
            to->raise();           // 保证窗口显示在最前
            to->activateWindow();  // 激活窗口防止主窗口缺失

        });

        to->setWindowOpacity(0);

        to->setGeometry(from->geometry());

        to->show();

        fadeIn->start();
    });

    fadeOut->start();
}

//----------------------------------构造析构--------------------------------------------

Animator::Animator(QObject* parent)
    : QObject(parent)
{
}

Animator::~Animator()
{
    if (m_animation && m_animation->state() == QAbstractAnimation::Running)
    {
        m_animation->stop();
    }
}

//----------------------------------公有方法--------------------------------------------

//回调函数
Animator* Animator::onFinished(std::function<void()> callback)
{
    if (m_animation)
    {
        connect(m_animation, &QPropertyAnimation::finished, this, std::move(callback));
    }

    return this;
}

//开始动画
Animator* Animator::start()
{
    if (!m_animation || m_animation->state() == QAbstractAnimation::Running)
    {
        qWarning("Animation not initialized or already running");
        return this;
    }

    m_animation->start();
    return this;
}

//----------------------------------私有方法--------------------------------------------

//建立动画
void Animator::setupAnimation(QWidget* target, AnimationType type, int duration)
{

    bool isTopLevel = target->isWindow();

    switch (type)
    {
        case FadeIn:
        case FadeOut:
            if (isTopLevel) //顶层窗口
            {
                m_animation = new QPropertyAnimation(target, "windowOpacity", target);

                if (type == FadeIn)
                {
                    target->setWindowOpacity(0.0);
                }
                else
                {
                    target->setWindowOpacity(1.0);
                }
            }
            else    //单个组件
            {
                m_opacityEffect = new QGraphicsOpacityEffect(target);
                target->setGraphicsEffect(m_opacityEffect);
                m_animation = new QPropertyAnimation(m_opacityEffect, "opacity", target);
            }

            if (type == FadeIn)
            {
                m_animation->setStartValue(0.0);
                m_animation->setEndValue(1.0);
            }
            else
            {
                m_animation->setStartValue(1.0);
                m_animation->setEndValue(0.0);
            }

            break;

        case SlideFromTop:
        {
            m_animation = new QPropertyAnimation(target, "pos", target);
            m_animation->setStartValue(QPoint(target->x() - rand() % 500 - 200, target->y() - rand() % 700 - 200));
            m_animation->setEndValue(target->pos());
        }

        break;
    }

    m_animation->setDuration(duration);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);

    //动画开始时设置可见
    connect(m_animation, &QAbstractAnimation::stateChanged, this, [target](QAbstractAnimation::State newState)
    {
        if (newState == QAbstractAnimation::Running)
        {
            target->setVisible(true);
        }
    });
}

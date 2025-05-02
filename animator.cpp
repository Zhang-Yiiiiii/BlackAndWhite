#include "animator.h"

Animator::Animator(QObject *parent)
    : QObject{parent}, m_animation(nullptr), m_opacityEffect(nullptr)
{

}

Animator* Animator::resetAnimation(AnimationType type)
{
    return this;
}

void Animator::setupAnimation(QWidget* target, AnimationType type)
{
    switch (type)
    {
        //渐进
        case FadeIn:
        {
            //设置透明效果
            m_opacityEffect = new QGraphicsOpacityEffect(target);
            target->setGraphicsEffect(m_opacityEffect);

            m_animation = new QPropertyAnimation(m_opacityEffect, "opacity", target);
            m_animation->setStartValue(0.0);
            m_animation->setEndValue(1.0);
            m_animation->setDuration(500);
            break;
        }

        //渐出
        case FadeOut:
        {
            //设置透明效果
            m_opacityEffect = new QGraphicsOpacityEffect(target);
            target->setGraphicsEffect(m_opacityEffect);

            m_animation = new QPropertyAnimation(m_opacityEffect, "opacity", target);
            m_animation->setStartValue(1.0);
            m_animation->setEndValue(0);
            m_animation->setDuration(1000);
            break;
        }

        //滑动进入
        case SlideFromTop:
        {
            m_animation = new QPropertyAnimation(target, "pos", target);
            m_animation->setStartValue(QPoint(target->x() - rand() % 2000, target->y() - rand() % 7000));
            m_animation->setEndValue(target->pos());
            m_animation->setDuration(600);
            break;
        }
    }

    connect(m_animation, &QPropertyAnimation::finished, [&]()   //让动画结束后回到原位置
    {
        //target->move(target->pos()); // 强制刷新位置
    });
}

Animator* Animator::createAnimator(QWidget * target, AnimationType type)
{
    Animator* animator = new Animator(target);
    animator->setupAnimation(target, type);
    //animator->m_animation->setDuration(500);
    animator->m_animation->setEasingCurve(QEasingCurve::OutQuad);

    return animator;
}

Animator* Animator::onFinished(std::function<void ()> callback)
{
    connect(m_animation, &QPropertyAnimation::finished, this, callback);

    return this; // 链式调用
}

Animator* Animator::start()
{
    //动画未被初始化 或者 动画正在运行
    if (!m_animation || m_animation->state() == QAbstractAnimation::Running)
    {
        qWarning() << "Animation is not initialized!";
        return this;
    }

    m_animation->start(); // 启动Qt原生动画
    return this; // 支持链式调用
}

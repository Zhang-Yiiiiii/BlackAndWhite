#include "animator.h"

Animator::Animator(QObject *parent)
    : QObject{parent}
{

}

Animator* Animator::resetAnimation(AnimationType type)
{

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

            m_animation = new QPropertyAnimation(m_opacityEffect, "opacity");
            m_animation->setStartValue(0.0);
            m_animation->setEndValue(1.0);
            break;
        }

        //渐出
        case FadeOut:
        {
            //设置透明效果
            m_opacityEffect = new QGraphicsOpacityEffect(target);
            target->setGraphicsEffect(m_opacityEffect);

            m_animation = new QPropertyAnimation(m_opacityEffect, "opacity");
            m_animation->setStartValue(1.0);
            m_animation->setEndValue(0);
            break;
        }

        //滑动进入
        case SlideFromTop:
        {
            m_animation = new QPropertyAnimation(target, "pos");
            m_animation->setStartValue(QPoint(target->x() - rand() % 200, target->y() - rand() % 700));
            m_animation->setEndValue(target->pos());
            break;
        }
    }

    connect(m_animation, &QPropertyAnimation::finished, [target]()   //让动画结束后回到原位置
    {
        target->move(target->pos()); // 强制刷新位置
    });
}

Animator* Animator::createAnimation(QWidget * target, AnimationType type)
{
    // if(m_animationPool.contains(target))
    // {
    // return m_animationPool[target];
    // }

    Animator* animator = new Animator(target);
    animator->setupAnimation(target, type);
    animator->m_animation->setDuration(500);
    animator->m_animation->setEasingCurve(QEasingCurve::OutQuad);

    // m_animationPool[target] = animator;

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

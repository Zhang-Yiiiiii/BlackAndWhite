#ifndef ANIMATOR_H
#define ANIMATOR_H

/*
 * class: Animator （动画类）
 *
 * 用处: 用于为组件提供动画、演示动画
 */

#include <QObject>
#include <QWidget>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMap>
#include <QList>

class Animator : public QObject
{
    Q_OBJECT
public:
    //动画类型
    enum AnimationType
    {
        FadeIn,
        FadeOut,
        SlideFromTop
    };

    //创建动画
    static Animator* createAnimator(QWidget* target, AnimationType type);

    //动画完成时的动作
    Animator* onFinished(std::function<void()> callback);

    //启动动画
    Animator* start();

private:

    explicit Animator(QObject *parent = nullptr);

    //重置动画
    Animator* resetAnimation(AnimationType type);

    //建立动画
    void setupAnimation(QWidget* target, AnimationType type);

    QPropertyAnimation* m_animation;    //动画

    QGraphicsOpacityEffect* m_opacityEffect; // 用于透明度动画

    //QWidget* m_widget;  //绑定对象

signals:

};

#endif // ANIMATOR_H

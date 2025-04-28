#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMap>

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
    static Animator* createAnimation(QWidget* target, AnimationType type);

    //动画完成时的动作
    Animator* onFinished(std::function<void()> callback);

    //启动动画
    Animator* start();
private:

    explicit Animator(QObject *parent = nullptr);

    //动画池
    static QMap<QWidget*, Animator*> m_animationPool;

    //重置动画
    Animator* resetAnimation(AnimationType type);

    //建立动画
    void setupAnimation(QWidget* target, AnimationType type);

    QPropertyAnimation* m_animation;

    QGraphicsOpacityEffect* m_opacityEffect; // 用于透明度动画

signals:

};

#endif // ANIMATOR_H

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <functional>

class Animator : public QObject
{
    Q_OBJECT
public:
    enum AnimationType
    {
        FadeIn,
        FadeOut,
        SlideFromTop
    };

    ~Animator();

    // 创建动画
    static Animator* createAnimator(QWidget* target, AnimationType type, int duration = 500);

    // 场景切换：淡出旧场景后淡入新场景
    static void transition(QWidget* from, QWidget* to, int duration = 500);

    // 动画完成回调
    Animator* onFinished(std::function<void()> callback);

    // 启动动画
    Animator* start();

private:
    explicit Animator(QObject* parent = nullptr);
    void setupAnimation(QWidget* target, AnimationType type, int duration);

    QPropertyAnimation* m_animation{nullptr};
    QGraphicsOpacityEffect* m_opacityEffect{nullptr};
};

#endif // ANIMATOR_H

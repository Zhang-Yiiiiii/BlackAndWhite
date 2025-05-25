#ifndef ANIMATOR_H
#define ANIMATOR_H

/*****************************************************************
 * class: Animator （动画类）
 *
 * 用处: 为组件创建动画、为窗口过渡添加动画
 *****************************************************************/

#include <QObject>
#include <QWidget>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QList>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPauseAnimation>

class Animator : public QObject
{
    Q_OBJECT
public:
    //------------------------公有类型----------------------------------

    enum AnimationType
    {
        FadeIn,
        FadeOut,
        SlideFromTop
    };

    //------------------------析构----------------------------------

    ~Animator();

    //------------------------静态方法----------------------------------

    // 创建动画
    static Animator* createAnimator(QWidget* target, AnimationType type, int duration = 400);

    // 场景切换：淡出旧场景后淡入新场景
    static void transition(QWidget* from, QWidget* to, int duration = 600);

    //------------------------公有方法----------------------------------

    // 动画完成回调
    Animator* onFinished(std::function<void()> callback);

    //动画开始的操作
    Animator* onStart(std::function<void()> callback);

    // 启动动画
    Animator* start();

private:
    //------------------------私有属性----------------------------------

    //动画
    QPropertyAnimation* m_animation{nullptr};

    //透明度
    QGraphicsOpacityEffect* m_opacityEffect{nullptr};

    //------------------------私有构造----------------------------------

    explicit Animator(QObject* parent = nullptr);

    //------------------------私有方法----------------------------------

    //建立动画
    void setupAnimation(QWidget* target, AnimationType type, int duration);

};

#endif // ANIMATOR_H

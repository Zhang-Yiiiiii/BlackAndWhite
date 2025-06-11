#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QPropertyAnimation>

/*****************************************************************
 * class: GridButton （格子类）
 *
 * 用处: 作为棋盘的格子，进行点击和翻转
 *****************************************************************/

class GridButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
public:

    explicit GridButton(bool flag, QWidget *parent = nullptr);

    void changeFlag(bool isShowAnimation = true, int duration = 300);   //翻转

    GridButton* setPos(int posx, int posy); //设置位置

    bool getFlag () const;  //获取状态

    int rotationAngle() const;  //翻转度数

    void setRotationAngle(int angle);   //设置翻转角度

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_posx = 0;
    int m_posy = 0;

    bool m_flag = true;
    bool m_animating = false;
    bool m_targetFlag;
    int m_rotationAngle = 0;

signals:
    void beClicked(int x, int y);
    void rotationAngleChanged();

};

#endif // GRIDBUTTON_H

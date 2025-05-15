// gridbutton.h
#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QPropertyAnimation>

class GridButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
public:
    explicit GridButton(bool flag, QWidget *parent = nullptr);
    void changeFlag();
    GridButton* setPos(int posx, int posy);

    int rotationAngle() const;
    void setRotationAngle(int angle);

private:
    int m_posx = 0;
    int m_posy = 0;
    QPixmap m_frontPix;
    QPixmap m_backPix;
    bool m_flag = true;
    bool m_animating = false;
    bool m_targetFlag;
    int m_rotationAngle = 0;

signals:
    void beClicked(int x, int y);
    void rotationAngleChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // GRIDBUTTON_H

#ifndef GRIDBUTTON_H
#define GRIDBUTTON_H

/*****************************************************************
 * class: GridButton （格子按钮）
 *
 * 用处: 作为游戏界面的棋盘、记录格子的正反情况、记录格子标号
 *****************************************************************/

#include <QWidget>
#include <QPushButton>
#include <QPixmap>

class GridButton : public QPushButton
{
    Q_OBJECT
public:

    //------------------------构造析构----------------------------------

    explicit GridButton(bool flag, QWidget *parent = nullptr);

    //------------------------公有方法----------------------------------

    //改变正反
    void changeFlag();

    //设置格子标号
    GridButton* setPos(int posx, int posy);

private:

    //------------------------私有属性----------------------------------

    //格子标号
    int m_posx = 0;
    int m_posy = 0;

    //加载图片
    QPixmap m_pix;

    //标志正反
    bool m_flag = true;   //true 表示格子为白色 false表示格子为黑色

signals:

    //------------------------信号----------------------------------

    void beClicked(int x, int y);
};

#endif // GRIDBUTTON_H

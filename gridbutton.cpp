#include "gridbutton.h"
#include "config.h"

GridButton::GridButton(bool flag, QWidget *parent)
    : QPushButton{parent}, m_flag(flag)
{
    //加载图片 设置大小
    if(flag)
    {
        m_pix.load(GRIDPATH1);    //根据flag加载图片
    }
    else
    {
        m_pix.load(GRIDPATH2);
    }

    //设置大小和图标
    this->setFixedSize(m_pix.size());
    this->setIcon(m_pix);
    this->setIconSize(m_pix.size());

    //改写被点击的信号发送
    connect(this, &QPushButton::clicked, this, [ = ]()
    {
        emit beClicked(m_posx, m_posy);
    });
};

void GridButton::changeFlag()
{

    if(m_flag)  //现在是白色 改成黑色
    {
        m_flag = false;
        m_pix.load(GRIDPATH2);
        this->setIcon(m_pix);
    }
    else
    {
        m_flag = true;
        m_pix.load(GRIDPATH1);
        this->setIcon(m_pix);
    }
}

GridButton* GridButton::setPos(int posx, int posy)
{
    if( posx < 0 || posy < 0)
    {
        return this;
    }

    m_posx = posx;
    m_posy = posy;

    return this;
}

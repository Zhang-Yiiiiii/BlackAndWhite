#include "gridbutton.h"
#include "config.h"

GridButton::GridButton(bool flag, QWidget *parent)
    : QPushButton{parent}, flag(flag)
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

    this->setFixedSize(m_pix.size());
    this->setIcon(m_pix);
    this->setIconSize(m_pix.size());
}

void GridButton::changeFlag()
{
    if(flag)  //现在是白色 改成黑色
    {
        flag = false;
        m_pix.load(GRIDPATH2);
        this->setIcon(m_pix);
    }
    else
    {
        flag = true;
        m_pix.load(GRIDPATH1);
        this->setIcon(m_pix);
    }
}

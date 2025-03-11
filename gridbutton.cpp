#include "gridbutton.h"

GridButton::GridButton(bool flag, QWidget *parent)
    : QPushButton{parent},flag(flag)
{
    //加载图片 设置大小
    if(flag) pix.load(GRIDPATH1); //根据flag加载图片
    else pix.load(GRIDPATH2);

    this->setFixedSize(pix.size());
    this->setIcon(pix);
    this->setIconSize(pix.size());

    // //如果被点击则改变状态
    // connect(this,&QPushButton::clicked,[=](){
    //     changeFlag();
    // });
}



void GridButton::changeFlag()
{
    if(flag)  //现在是白色 改成黑色
    {
        flag = false;
        pix.load(GRIDPATH2);
        this->setIcon(pix);
    }
    else
    {
        flag = true;
        pix.load(GRIDPATH1);
        this->setIcon(pix);
    }
}

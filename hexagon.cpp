#include "hexagon.h"


Hexagon::Hexagon(int id ,QPushButton * parent):
    QPushButton(parent) ,id(id+1)
{
    //加载按钮图片资源
    pix.load(HEXAGONPATH);
    //设置按钮大小
    this->setFixedSize(pix.size());
    //设置边框为不规则
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

    //test
    // connect(this,&QPushButton::clicked,[=](){
    //     qDebug()<<"点击按钮"<<this->id;
    // });


    //设置按钮的文字
    this->setText(QString::number(this->id));

    //告诉主场景被点击
    connect(this,&QPushButton::clicked,[=](){
        emit beClicked(this->id);
    });

}

//重写绘图事件
void Hexagon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制图标
    painter.drawPixmap(0,0,pix);

    // 绘制文本
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    painter.setPen(Qt::white); // 设置文本颜色为白色（可根据需要调整）
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, text()); // 文本居中显示
}

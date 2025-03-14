#include "mainscene.h"

#include <QApplication>
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;

    // 设置全局字体
    QFont font("华文新魏", 15);
    a.setFont(font);

    w.show();
    return a.exec();
}

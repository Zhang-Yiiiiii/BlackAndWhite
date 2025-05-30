#include "mainscene.h"

#include <QApplication>
#include <QFont>

#include "config.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    MainScene w;

    //设置全局字体
    //a.setFont(QFont("华文新魏", 15));

    //设置图标
    a.setWindowIcon(QIcon(MYICON));

    w.show();

    return a.exec();
}

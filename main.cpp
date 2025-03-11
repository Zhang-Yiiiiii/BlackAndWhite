#include "mainscene.h"

#include <QApplication>
#include <iostream>
#include <fstream>


int main(int argc, char *argv[])
{
    // ifstream ifs;
    // ifs.open("data")

    QApplication a(argc, argv);
    MainScene w;
    w.show();
    return a.exec();
}

#include "mainscene.h"

#include <QApplication>
#include <QFont>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF
                   | _CRTDBG_CHECK_ALWAYS_DF);

    QApplication a(argc, argv);
    MainScene w;

    // 设置全局字体
    QFont font("华文新魏", 15);
    a.setFont(font);

    a.setWindowIcon(QIcon(MYICON));

    w.show();

    return a.exec();
}

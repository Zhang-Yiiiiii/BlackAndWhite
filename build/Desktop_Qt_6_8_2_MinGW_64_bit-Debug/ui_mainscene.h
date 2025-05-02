/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScene
{
public:
    QAction *actionquit;
    QAction *actionsave;
    QAction *actioninstruction;
    QAction *actionstartingPoint;
    QAction *actiondestination;
    QAction *actionLogin;
    QAction *online;
    QAction *lightBuildMapAction;
    QAction *disConnect;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *menu_3;

    void setupUi(QMainWindow *MainScene)
    {
        if (MainScene->objectName().isEmpty())
            MainScene->setObjectName("MainScene");
        MainScene->resize(800, 600);
        actionquit = new QAction(MainScene);
        actionquit->setObjectName("actionquit");
        actionsave = new QAction(MainScene);
        actionsave->setObjectName("actionsave");
        actioninstruction = new QAction(MainScene);
        actioninstruction->setObjectName("actioninstruction");
        actionstartingPoint = new QAction(MainScene);
        actionstartingPoint->setObjectName("actionstartingPoint");
        actiondestination = new QAction(MainScene);
        actiondestination->setObjectName("actiondestination");
        actionLogin = new QAction(MainScene);
        actionLogin->setObjectName("actionLogin");
        online = new QAction(MainScene);
        online->setObjectName("online");
        lightBuildMapAction = new QAction(MainScene);
        lightBuildMapAction->setObjectName("lightBuildMapAction");
        disConnect = new QAction(MainScene);
        disConnect->setObjectName("disConnect");
        centralwidget = new QWidget(MainScene);
        centralwidget->setObjectName("centralwidget");
        MainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainScene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menubar->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Microsoft YaHei UI\";\n"
"background-color: rgba(217, 217, 217, 150);\n"
"color: rgb(66, 66, 66);"));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_4 = new QMenu(menu_2);
        menu_4->setObjectName("menu_4");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        MainScene->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(actionquit);
        menu->addAction(actionsave);
        menu->addAction(actionLogin);
        menu_2->addAction(menu_4->menuAction());
        menu_2->addAction(actioninstruction);
        menu_2->addAction(lightBuildMapAction);
        menu_4->addAction(actionstartingPoint);
        menu_4->addAction(actiondestination);
        menu_3->addAction(online);
        menu_3->addAction(disConnect);

        retranslateUi(MainScene);

        QMetaObject::connectSlotsByName(MainScene);
    } // setupUi

    void retranslateUi(QMainWindow *MainScene)
    {
        MainScene->setWindowTitle(QCoreApplication::translate("MainScene", "MainScene", nullptr));
        actionquit->setText(QCoreApplication::translate("MainScene", "\351\200\200\345\207\272", nullptr));
        actionsave->setText(QCoreApplication::translate("MainScene", "\344\277\235\345\255\230", nullptr));
        actioninstruction->setText(QCoreApplication::translate("MainScene", "\350\257\264\346\230\216", nullptr));
        actionstartingPoint->setText(QCoreApplication::translate("MainScene", "\350\265\267\347\202\271\345\273\272\345\233\276", nullptr));
        actionstartingPoint->setIconText(QCoreApplication::translate("MainScene", "\350\265\267\347\202\271\345\273\272\345\233\276", nullptr));
        actiondestination->setText(QCoreApplication::translate("MainScene", "\347\273\210\347\202\271\345\273\272\345\233\276", nullptr));
        actionLogin->setText(QCoreApplication::translate("MainScene", "\347\231\273\345\275\225", nullptr));
        online->setText(QCoreApplication::translate("MainScene", "\350\201\224\346\234\272", nullptr));
        lightBuildMapAction->setText(QCoreApplication::translate("MainScene", "\347\206\204\347\201\257\346\270\270\346\210\217\350\207\252\345\273\272\345\234\260\345\233\276", nullptr));
        disConnect->setText(QCoreApplication::translate("MainScene", "\346\226\255\345\274\200\350\201\224\346\234\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainScene", "\345\274\200\345\247\213", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainScene", "\346\270\270\346\210\217", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainScene", "\345\205\260\351\241\277\350\232\202\350\232\201\350\207\252\345\273\272\345\234\260\345\233\276", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainScene", "\345\267\245\345\205\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScene: public Ui_MainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H

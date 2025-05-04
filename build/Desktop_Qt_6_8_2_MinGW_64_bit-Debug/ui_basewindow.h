/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName("BaseWindow");
        BaseWindow->resize(320, 240);
        centralwidget = new QWidget(BaseWindow);
        centralwidget->setObjectName("centralwidget");
        BaseWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BaseWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 320, 17));
        BaseWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BaseWindow);
        statusbar->setObjectName("statusbar");
        BaseWindow->setStatusBar(statusbar);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindow)
    {
        BaseWindow->setWindowTitle(QCoreApplication::translate("BaseWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myDialog
{
public:
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
    QLineEdit *lineEdit4;
    QLineEdit *lineEdit5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *confirmButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *myDialog)
    {
        if (myDialog->objectName().isEmpty())
            myDialog->setObjectName("myDialog");
        myDialog->resize(550, 440);
        widget_3 = new QWidget(myDialog);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(80, 50, 381, 281));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget_2);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);


        horizontalLayout->addWidget(widget_2);

        widget = new QWidget(widget_3);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        lineEdit1 = new QLineEdit(widget);
        lineEdit1->setObjectName("lineEdit1");

        verticalLayout->addWidget(lineEdit1);

        lineEdit2 = new QLineEdit(widget);
        lineEdit2->setObjectName("lineEdit2");

        verticalLayout->addWidget(lineEdit2);

        lineEdit3 = new QLineEdit(widget);
        lineEdit3->setObjectName("lineEdit3");

        verticalLayout->addWidget(lineEdit3);

        lineEdit4 = new QLineEdit(widget);
        lineEdit4->setObjectName("lineEdit4");

        verticalLayout->addWidget(lineEdit4);

        lineEdit5 = new QLineEdit(widget);
        lineEdit5->setObjectName("lineEdit5");

        verticalLayout->addWidget(lineEdit5);


        horizontalLayout->addWidget(widget);

        label_6 = new QLabel(myDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 10, 151, 25));
        label_7 = new QLabel(myDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(70, 340, 421, 25));
        confirmButton = new QPushButton(myDialog);
        confirmButton->setObjectName("confirmButton");
        confirmButton->setGeometry(QRect(330, 390, 81, 34));
        cancelButton = new QPushButton(myDialog);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(447, 390, 81, 34));

        retranslateUi(myDialog);

        QMetaObject::connectSlotsByName(myDialog);
    } // setupUi

    void retranslateUi(QDialog *myDialog)
    {
        myDialog->setWindowTitle(QCoreApplication::translate("myDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("myDialog", "\345\205\263\345\215\241\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("myDialog", "\346\255\245\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("myDialog", "bug\346\211\200\345\234\250\350\241\214", nullptr));
        label_4->setText(QCoreApplication::translate("myDialog", "bug\346\211\200\345\234\250\345\210\227", nullptr));
        label_5->setText(QCoreApplication::translate("myDialog", "bug\346\226\271\345\220\221", nullptr));
        label_6->setText(QCoreApplication::translate("myDialog", "\350\257\267\345\241\253\345\206\231\344\270\213\345\210\227\344\277\241\346\201\257", nullptr));
        label_7->setText(QCoreApplication::translate("myDialog", "\346\226\271\345\220\221\344\270\2720\357\274\2141\357\274\2142\357\274\2143\357\274\233\345\210\206\345\210\253\345\257\271\345\272\224\345\267\246\357\274\214\344\270\212\357\274\214\345\217\263\357\274\214\344\270\213", nullptr));
        confirmButton->setText(QCoreApplication::translate("myDialog", "\347\241\256\345\256\232", nullptr));
        cancelButton->setText(QCoreApplication::translate("myDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_myDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H

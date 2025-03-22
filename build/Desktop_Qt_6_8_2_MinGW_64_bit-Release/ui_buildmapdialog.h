/********************************************************************************
** Form generated from reading UI file 'buildmapdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDMAPDIALOG_H
#define UI_BUILDMAPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildMapDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_7;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit1;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit2;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *lineEdit3;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *lineEdit4;
    QSpacerItem *verticalSpacer_5;
    QLineEdit *lineEdit5;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *confirmButton;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_10;

    void setupUi(QDialog *BuildMapDialog)
    {
        if (BuildMapDialog->objectName().isEmpty())
            BuildMapDialog->setObjectName("BuildMapDialog");
        BuildMapDialog->resize(541, 392);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BuildMapDialog->sizePolicy().hasHeightForWidth());
        BuildMapDialog->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        BuildMapDialog->setFont(font);
        gridLayout = new QGridLayout(BuildMapDialog);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_6 = new QLabel(BuildMapDialog);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label_6->setFont(font1);

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        widget_2 = new QWidget(BuildMapDialog);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget_2);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(70, 25));
        label->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setBold(false);
        label->setFont(font2);
        label->setTextFormat(Qt::TextFormat::RichText);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        verticalSpacer = new QSpacerItem(50, 23, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(70, 25));
        label_2->setMaximumSize(QSize(16777215, 40));
        label_2->setFont(font2);
        label_2->setTextFormat(Qt::TextFormat::RichText);
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        verticalSpacer_6 = new QSpacerItem(50, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(70, 25));
        label_3->setMaximumSize(QSize(16777215, 40));
        label_3->setFont(font2);
        label_3->setTextFormat(Qt::TextFormat::RichText);
        label_3->setScaledContents(true);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_7 = new QSpacerItem(50, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(70, 25));
        label_4->setMaximumSize(QSize(16777215, 40));
        label_4->setFont(font2);
        label_4->setTextFormat(Qt::TextFormat::RichText);
        label_4->setScaledContents(true);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        verticalSpacer_8 = new QSpacerItem(50, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(70, 25));
        label_5->setMaximumSize(QSize(16777215, 40));
        label_5->setFont(font2);
        label_5->setTextFormat(Qt::TextFormat::RichText);
        label_5->setScaledContents(true);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_5);


        horizontalLayout->addWidget(widget_2);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        widget = new QWidget(BuildMapDialog);
        widget->setObjectName("widget");
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        lineEdit1 = new QLineEdit(widget);
        lineEdit1->setObjectName("lineEdit1");
        sizePolicy2.setHeightForWidth(lineEdit1->sizePolicy().hasHeightForWidth());
        lineEdit1->setSizePolicy(sizePolicy2);
        lineEdit1->setMinimumSize(QSize(0, 25));
        lineEdit1->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(lineEdit1);

        verticalSpacer_2 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        lineEdit2 = new QLineEdit(widget);
        lineEdit2->setObjectName("lineEdit2");
        sizePolicy2.setHeightForWidth(lineEdit2->sizePolicy().hasHeightForWidth());
        lineEdit2->setSizePolicy(sizePolicy2);
        lineEdit2->setMinimumSize(QSize(0, 25));
        lineEdit2->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(lineEdit2);

        verticalSpacer_3 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        lineEdit3 = new QLineEdit(widget);
        lineEdit3->setObjectName("lineEdit3");
        sizePolicy2.setHeightForWidth(lineEdit3->sizePolicy().hasHeightForWidth());
        lineEdit3->setSizePolicy(sizePolicy2);
        lineEdit3->setMinimumSize(QSize(0, 25));
        lineEdit3->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(lineEdit3);

        verticalSpacer_4 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        lineEdit4 = new QLineEdit(widget);
        lineEdit4->setObjectName("lineEdit4");
        sizePolicy2.setHeightForWidth(lineEdit4->sizePolicy().hasHeightForWidth());
        lineEdit4->setSizePolicy(sizePolicy2);
        lineEdit4->setMinimumSize(QSize(0, 25));
        lineEdit4->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(lineEdit4);

        verticalSpacer_5 = new QSpacerItem(20, 25, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        lineEdit5 = new QLineEdit(widget);
        lineEdit5->setObjectName("lineEdit5");
        sizePolicy2.setHeightForWidth(lineEdit5->sizePolicy().hasHeightForWidth());
        lineEdit5->setSizePolicy(sizePolicy2);
        lineEdit5->setMinimumSize(QSize(0, 25));
        lineEdit5->setMaximumSize(QSize(16777215, 25));

        verticalLayout->addWidget(lineEdit5);


        horizontalLayout->addWidget(widget);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        label_7 = new QLabel(BuildMapDialog);
        label_7->setObjectName("label_7");
        label_7->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        confirmButton = new QPushButton(BuildMapDialog);
        confirmButton->setObjectName("confirmButton");

        horizontalLayout_4->addWidget(confirmButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        cancelButton = new QPushButton(BuildMapDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout_4->addWidget(cancelButton);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        retranslateUi(BuildMapDialog);

        QMetaObject::connectSlotsByName(BuildMapDialog);
    } // setupUi

    void retranslateUi(QDialog *BuildMapDialog)
    {
        BuildMapDialog->setWindowTitle(QCoreApplication::translate("BuildMapDialog", "Dialog", nullptr));
        label_6->setText(QCoreApplication::translate("BuildMapDialog", "\350\257\267\345\241\253\345\206\231\344\270\213\345\210\227\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("BuildMapDialog", "\345\205\263\345\215\241\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("BuildMapDialog", "\346\255\245\346\225\260", nullptr));
        label_3->setText(QCoreApplication::translate("BuildMapDialog", "bug\346\211\200\345\234\250\350\241\214", nullptr));
        label_4->setText(QCoreApplication::translate("BuildMapDialog", "bug\346\211\200\345\234\250\345\210\227", nullptr));
        label_5->setText(QCoreApplication::translate("BuildMapDialog", "bug\346\226\271\345\220\221", nullptr));
        label_7->setText(QCoreApplication::translate("BuildMapDialog", "\346\226\271\345\220\221\344\270\2720\357\274\2141\357\274\2142\357\274\2143\357\274\233\345\210\206\345\210\253\345\257\271\345\272\224\345\267\246\357\274\214\344\270\212\357\274\214\345\217\263\357\274\214\344\270\213", nullptr));
        confirmButton->setText(QCoreApplication::translate("BuildMapDialog", "\347\241\256\345\256\232", nullptr));
        cancelButton->setText(QCoreApplication::translate("BuildMapDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuildMapDialog: public Ui_BuildMapDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDMAPDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'onlinewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINEWINDOW_H
#define UI_ONLINEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelLogin;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *ipLabel;
    QLineEdit *ipEdit;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *listenBtn;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *joinBtn;
    QSpacerItem *horizontalSpacer_7;
    QMenuBar *menubar;

    void setupUi(QMainWindow *OnlineWindow)
    {
        if (OnlineWindow->objectName().isEmpty())
            OnlineWindow->setObjectName("OnlineWindow");
        OnlineWindow->resize(453, 473);
        centralwidget = new QWidget(OnlineWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        labelLogin = new QLabel(centralwidget);
        labelLogin->setObjectName("labelLogin");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelLogin->sizePolicy().hasHeightForWidth());
        labelLogin->setSizePolicy(sizePolicy);
        labelLogin->setMinimumSize(QSize(180, 30));
        labelLogin->setMaximumSize(QSize(180, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(25);
        font.setBold(true);
        labelLogin->setFont(font);
        labelLogin->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(labelLogin);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(50, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ipLabel = new QLabel(centralwidget);
        ipLabel->setObjectName("ipLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ipLabel->sizePolicy().hasHeightForWidth());
        ipLabel->setSizePolicy(sizePolicy1);
        ipLabel->setMinimumSize(QSize(40, 30));
        ipLabel->setMaximumSize(QSize(40, 30));
        QFont font1;
        font1.setPointSize(12);
        ipLabel->setFont(font1);
        ipLabel->setTextFormat(Qt::TextFormat::RichText);
        ipLabel->setScaledContents(true);
        ipLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(ipLabel);

        ipEdit = new QLineEdit(centralwidget);
        ipEdit->setObjectName("ipEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ipEdit->sizePolicy().hasHeightForWidth());
        ipEdit->setSizePolicy(sizePolicy2);
        ipEdit->setMinimumSize(QSize(320, 20));
        ipEdit->setMaximumSize(QSize(380, 25));
        ipEdit->setStyleSheet(QString::fromUtf8("color: black"));
        ipEdit->setFrame(true);

        horizontalLayout->addWidget(ipEdit);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_23);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        portLabel = new QLabel(centralwidget);
        portLabel->setObjectName("portLabel");
        sizePolicy1.setHeightForWidth(portLabel->sizePolicy().hasHeightForWidth());
        portLabel->setSizePolicy(sizePolicy1);
        portLabel->setMinimumSize(QSize(40, 30));
        portLabel->setMaximumSize(QSize(40, 30));
        portLabel->setFont(font1);
        portLabel->setScaledContents(true);
        portLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(portLabel);

        portEdit = new QLineEdit(centralwidget);
        portEdit->setObjectName("portEdit");
        sizePolicy2.setHeightForWidth(portEdit->sizePolicy().hasHeightForWidth());
        portEdit->setSizePolicy(sizePolicy2);
        portEdit->setMinimumSize(QSize(320, 20));
        portEdit->setMaximumSize(QSize(380, 25));
        portEdit->setAutoFillBackground(false);
        portEdit->setStyleSheet(QString::fromUtf8("color: black"));
        portEdit->setFrame(true);
        portEdit->setEchoMode(QLineEdit::EchoMode::Normal);

        horizontalLayout_2->addWidget(portEdit);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 5, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        listenBtn = new QPushButton(centralwidget);
        listenBtn->setObjectName("listenBtn");
        sizePolicy1.setHeightForWidth(listenBtn->sizePolicy().hasHeightForWidth());
        listenBtn->setSizePolicy(sizePolicy1);
        listenBtn->setMinimumSize(QSize(120, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(20);
        font2.setBold(true);
        listenBtn->setFont(font2);
        listenBtn->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(listenBtn);

        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_7, 6, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        joinBtn = new QPushButton(centralwidget);
        joinBtn->setObjectName("joinBtn");
        sizePolicy1.setHeightForWidth(joinBtn->sizePolicy().hasHeightForWidth());
        joinBtn->setSizePolicy(sizePolicy1);
        joinBtn->setMinimumSize(QSize(120, 30));
        joinBtn->setMaximumSize(QSize(16777215, 30));
        joinBtn->setFont(font2);
        joinBtn->setIconSize(QSize(16, 16));

        horizontalLayout_6->addWidget(joinBtn);

        horizontalSpacer_7 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_6, 7, 0, 1, 1);

        OnlineWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OnlineWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 453, 17));
        OnlineWindow->setMenuBar(menubar);

        retranslateUi(OnlineWindow);

        QMetaObject::connectSlotsByName(OnlineWindow);
    } // setupUi

    void retranslateUi(QMainWindow *OnlineWindow)
    {
        OnlineWindow->setWindowTitle(QCoreApplication::translate("OnlineWindow", "MainWindow", nullptr));
        labelLogin->setText(QCoreApplication::translate("OnlineWindow", "On-Line", nullptr));
        ipLabel->setText(QCoreApplication::translate("OnlineWindow", "IP", nullptr));
        portLabel->setText(QCoreApplication::translate("OnlineWindow", "PORT", nullptr));
        listenBtn->setText(QCoreApplication::translate("OnlineWindow", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        joinBtn->setText(QCoreApplication::translate("OnlineWindow", "\345\212\240\345\205\245\346\210\277\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OnlineWindow: public Ui_OnlineWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINEWINDOW_H

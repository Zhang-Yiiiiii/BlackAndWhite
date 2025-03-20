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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OnlineWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_21;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
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
    QFrame *framePic;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_22;
    QFrame *frameBackgroud;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OnlineWindow)
    {
        if (OnlineWindow->objectName().isEmpty())
            OnlineWindow->setObjectName("OnlineWindow");
        OnlineWindow->resize(655, 397);
        centralwidget = new QWidget(OnlineWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 0, 634, 359));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalSpacer_21 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_21);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        labelLogin = new QLabel(layoutWidget);
        labelLogin->setObjectName("labelLogin");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelLogin->sizePolicy().hasHeightForWidth());
        labelLogin->setSizePolicy(sizePolicy);
        labelLogin->setMinimumSize(QSize(180, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(25);
        font.setBold(true);
        labelLogin->setFont(font);
        labelLogin->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(labelLogin);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(50, 50, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        ipLabel = new QLabel(layoutWidget);
        ipLabel->setObjectName("ipLabel");
        sizePolicy.setHeightForWidth(ipLabel->sizePolicy().hasHeightForWidth());
        ipLabel->setSizePolicy(sizePolicy);
        ipLabel->setMinimumSize(QSize(30, 30));
        ipLabel->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setPointSize(12);
        ipLabel->setFont(font1);
        ipLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(ipLabel);

        ipEdit = new QLineEdit(layoutWidget);
        ipEdit->setObjectName("ipEdit");
        sizePolicy.setHeightForWidth(ipEdit->sizePolicy().hasHeightForWidth());
        ipEdit->setSizePolicy(sizePolicy);
        ipEdit->setMinimumSize(QSize(140, 20));
        ipEdit->setMaximumSize(QSize(140, 25));
        ipEdit->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        ipEdit->setFrame(true);

        horizontalLayout->addWidget(ipEdit);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_23 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_23);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        portLabel = new QLabel(layoutWidget);
        portLabel->setObjectName("portLabel");
        sizePolicy.setHeightForWidth(portLabel->sizePolicy().hasHeightForWidth());
        portLabel->setSizePolicy(sizePolicy);
        portLabel->setMinimumSize(QSize(30, 30));
        portLabel->setMaximumSize(QSize(30, 30));
        portLabel->setFont(font1);
        portLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(portLabel);

        portEdit = new QLineEdit(layoutWidget);
        portEdit->setObjectName("portEdit");
        sizePolicy.setHeightForWidth(portEdit->sizePolicy().hasHeightForWidth());
        portEdit->setSizePolicy(sizePolicy);
        portEdit->setMinimumSize(QSize(140, 20));
        portEdit->setMaximumSize(QSize(140, 25));
        portEdit->setAutoFillBackground(true);
        portEdit->setStyleSheet(QString::fromUtf8(""));
        portEdit->setFrame(true);
        portEdit->setEchoMode(QLineEdit::EchoMode::Normal);

        horizontalLayout_2->addWidget(portEdit);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        listenBtn = new QPushButton(layoutWidget);
        listenBtn->setObjectName("listenBtn");
        sizePolicy.setHeightForWidth(listenBtn->sizePolicy().hasHeightForWidth());
        listenBtn->setSizePolicy(sizePolicy);
        listenBtn->setMinimumSize(QSize(100, 30));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(23);
        font2.setBold(true);
        listenBtn->setFont(font2);
        listenBtn->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(listenBtn);

        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        joinBtn = new QPushButton(layoutWidget);
        joinBtn->setObjectName("joinBtn");
        sizePolicy.setHeightForWidth(joinBtn->sizePolicy().hasHeightForWidth());
        joinBtn->setSizePolicy(sizePolicy);
        joinBtn->setMinimumSize(QSize(100, 30));
        joinBtn->setFont(font2);
        joinBtn->setIconSize(QSize(16, 16));

        horizontalLayout_6->addWidget(joinBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_15->addLayout(verticalLayout);

        framePic = new QFrame(layoutWidget);
        framePic->setObjectName("framePic");
        sizePolicy.setHeightForWidth(framePic->sizePolicy().hasHeightForWidth());
        framePic->setSizePolicy(sizePolicy);
        framePic->setMinimumSize(QSize(234, 341));
        framePic->setMaximumSize(QSize(234, 341));
        framePic->setFrameShape(QFrame::Shape::NoFrame);
        framePic->setFrameShadow(QFrame::Shadow::Sunken);
        gridLayout_3 = new QGridLayout(framePic);
        gridLayout_3->setObjectName("gridLayout_3");

        horizontalLayout_15->addWidget(framePic);

        horizontalSpacer_22 = new QSpacerItem(18, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_22);


        gridLayout->addLayout(horizontalLayout_15, 1, 1, 1, 1);

        frameBackgroud = new QFrame(layoutWidget);
        frameBackgroud->setObjectName("frameBackgroud");
        frameBackgroud->setFrameShape(QFrame::Shape::StyledPanel);
        frameBackgroud->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout->addWidget(frameBackgroud, 0, 0, 1, 1);

        OnlineWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OnlineWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 655, 17));
        OnlineWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(OnlineWindow);
        statusbar->setObjectName("statusbar");
        OnlineWindow->setStatusBar(statusbar);

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

/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QGridLayout *gridLayout_2;
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
    QLabel *labelUsername;
    QLineEdit *userNameEdit;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPassword;
    QLineEdit *passwdEdit;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *registerButton;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_10;
    QFrame *framePic;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_22;
    QFrame *frameBackgroud;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(574, 361);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setWindowOpacity(1.000000000000000);
        LoginWindow->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(LoginWindow);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
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

        labelLogin = new QLabel(LoginWindow);
        labelLogin->setObjectName("labelLogin");
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
        labelUsername = new QLabel(LoginWindow);
        labelUsername->setObjectName("labelUsername");
        sizePolicy.setHeightForWidth(labelUsername->sizePolicy().hasHeightForWidth());
        labelUsername->setSizePolicy(sizePolicy);
        labelUsername->setMinimumSize(QSize(30, 30));
        labelUsername->setMaximumSize(QSize(30, 30));
        QFont font1;
        font1.setPointSize(12);
        labelUsername->setFont(font1);
        labelUsername->setPixmap(QPixmap(QString::fromUtf8(":/icon/userAccountIcon.png")));

        horizontalLayout->addWidget(labelUsername);

        userNameEdit = new QLineEdit(LoginWindow);
        userNameEdit->setObjectName("userNameEdit");
        sizePolicy.setHeightForWidth(userNameEdit->sizePolicy().hasHeightForWidth());
        userNameEdit->setSizePolicy(sizePolicy);
        userNameEdit->setMinimumSize(QSize(140, 20));
        userNameEdit->setMaximumSize(QSize(140, 25));
        userNameEdit->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        userNameEdit->setFrame(true);

        horizontalLayout->addWidget(userNameEdit);


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
        labelPassword = new QLabel(LoginWindow);
        labelPassword->setObjectName("labelPassword");
        sizePolicy.setHeightForWidth(labelPassword->sizePolicy().hasHeightForWidth());
        labelPassword->setSizePolicy(sizePolicy);
        labelPassword->setMinimumSize(QSize(30, 30));
        labelPassword->setMaximumSize(QSize(30, 30));
        labelPassword->setFont(font1);
        labelPassword->setPixmap(QPixmap(QString::fromUtf8(":/icon/passwordIcon.png")));

        horizontalLayout_2->addWidget(labelPassword);

        passwdEdit = new QLineEdit(LoginWindow);
        passwdEdit->setObjectName("passwdEdit");
        sizePolicy.setHeightForWidth(passwdEdit->sizePolicy().hasHeightForWidth());
        passwdEdit->setSizePolicy(sizePolicy);
        passwdEdit->setMinimumSize(QSize(140, 20));
        passwdEdit->setMaximumSize(QSize(140, 25));
        passwdEdit->setAutoFillBackground(true);
        passwdEdit->setStyleSheet(QString::fromUtf8(""));
        passwdEdit->setFrame(true);
        passwdEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(passwdEdit);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        registerButton = new QPushButton(LoginWindow);
        registerButton->setObjectName("registerButton");
        sizePolicy.setHeightForWidth(registerButton->sizePolicy().hasHeightForWidth());
        registerButton->setSizePolicy(sizePolicy);
        registerButton->setMinimumSize(QSize(85, 25));
        registerButton->setMaximumSize(QSize(85, 25));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(14);
        font2.setWeight(QFont::Medium);
        registerButton->setFont(font2);
        registerButton->setAutoFillBackground(true);

        horizontalLayout_6->addWidget(registerButton);

        horizontalSpacer_8 = new QSpacerItem(35, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");
        sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy);
        loginButton->setMinimumSize(QSize(100, 30));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(23);
        font3.setBold(true);
        loginButton->setFont(font3);
        loginButton->setIconSize(QSize(16, 16));

        horizontalLayout_7->addWidget(loginButton);

        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout_15->addLayout(verticalLayout);

        framePic = new QFrame(LoginWindow);
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

        frameBackgroud = new QFrame(LoginWindow);
        frameBackgroud->setObjectName("frameBackgroud");
        frameBackgroud->setFrameShape(QFrame::Shape::StyledPanel);
        frameBackgroud->setFrameShadow(QFrame::Shadow::Raised);

        gridLayout->addWidget(frameBackgroud, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(userNameEdit, passwdEdit);
        QWidget::setTabOrder(passwdEdit, registerButton);
        QWidget::setTabOrder(registerButton, loginButton);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        labelLogin->setText(QCoreApplication::translate("LoginWindow", "LOGIN", nullptr));
        labelUsername->setText(QString());
        labelPassword->setText(QString());
        registerButton->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273    \345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

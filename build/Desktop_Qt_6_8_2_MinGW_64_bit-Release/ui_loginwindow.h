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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QGridLayout *gridLayout;
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

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(502, 391);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        LoginWindow->setWindowOpacity(1.000000000000000);
        LoginWindow->setAutoFillBackground(false);
        gridLayout = new QGridLayout(LoginWindow);
        gridLayout->setObjectName("gridLayout");
        verticalSpacer = new QSpacerItem(20, 27, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        labelLogin = new QLabel(LoginWindow);
        labelLogin->setObjectName("labelLogin");
        sizePolicy.setHeightForWidth(labelLogin->sizePolicy().hasHeightForWidth());
        labelLogin->setSizePolicy(sizePolicy);
        labelLogin->setMinimumSize(QSize(400, 40));
        labelLogin->setMaximumSize(QSize(400, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(25);
        font.setBold(true);
        labelLogin->setFont(font);
        labelLogin->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(labelLogin);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(50, 45, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelUsername = new QLabel(LoginWindow);
        labelUsername->setObjectName("labelUsername");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelUsername->sizePolicy().hasHeightForWidth());
        labelUsername->setSizePolicy(sizePolicy1);
        labelUsername->setMinimumSize(QSize(30, 30));
        labelUsername->setMaximumSize(QSize(999, 999));
        QFont font1;
        font1.setPointSize(12);
        labelUsername->setFont(font1);
        labelUsername->setPixmap(QPixmap(QString::fromUtf8(":/icon/userAccountIcon.png")));

        horizontalLayout->addWidget(labelUsername);

        userNameEdit = new QLineEdit(LoginWindow);
        userNameEdit->setObjectName("userNameEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(userNameEdit->sizePolicy().hasHeightForWidth());
        userNameEdit->setSizePolicy(sizePolicy2);
        userNameEdit->setMinimumSize(QSize(320, 30));
        userNameEdit->setMaximumSize(QSize(380, 9999));
        userNameEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
" {\n"
"      background-color: gba(255, 255, 255, 0.8);\n"
"    color: white;\n"
" }\357\274\233\n"
"\n"
" QLineEdit::placeholder\n"
" {\n"
"    color: rgba(255, 255, 255, 1); \n"
" }\357\274\233\n"
""));
        userNameEdit->setFrame(true);
        userNameEdit->setClearButtonEnabled(false);

        horizontalLayout->addWidget(userNameEdit);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalSpacer_23 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_23);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 27, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labelPassword = new QLabel(LoginWindow);
        labelPassword->setObjectName("labelPassword");
        sizePolicy1.setHeightForWidth(labelPassword->sizePolicy().hasHeightForWidth());
        labelPassword->setSizePolicy(sizePolicy1);
        labelPassword->setMinimumSize(QSize(30, 30));
        labelPassword->setMaximumSize(QSize(999, 999));
        labelPassword->setFont(font1);
        labelPassword->setPixmap(QPixmap(QString::fromUtf8(":/icon/passwordIcon.png")));

        horizontalLayout_2->addWidget(labelPassword);

        passwdEdit = new QLineEdit(LoginWindow);
        passwdEdit->setObjectName("passwdEdit");
        sizePolicy2.setHeightForWidth(passwdEdit->sizePolicy().hasHeightForWidth());
        passwdEdit->setSizePolicy(sizePolicy2);
        passwdEdit->setMinimumSize(QSize(320, 30));
        passwdEdit->setMaximumSize(QSize(380, 9999));
        passwdEdit->setAutoFillBackground(false);
        passwdEdit->setStyleSheet(QString::fromUtf8("QLineEdit\n"
" {\n"
"      background-color: gba(255, 255, 255, 0.8);\n"
"    color: white;\n"
" }\357\274\233\n"
"\n"
" QLineEdit::placeholder\n"
" {\n"
"    color: rgba(255, 255, 255, 1); \n"
" }\357\274\233\n"
""));
        passwdEdit->setFrame(true);
        passwdEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(passwdEdit);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_3, 5, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 28, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_4, 6, 0, 1, 1);

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


        gridLayout->addLayout(horizontalLayout_6, 7, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 27, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        gridLayout->addItem(verticalSpacer_5, 8, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer_9 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

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

        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_7, 9, 0, 1, 1);

        QWidget::setTabOrder(userNameEdit, passwdEdit);
        QWidget::setTabOrder(passwdEdit, registerButton);
        QWidget::setTabOrder(registerButton, loginButton);

        retranslateUi(LoginWindow);

        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        labelLogin->setText(QCoreApplication::translate("LoginWindow", "LOGIN", nullptr));
        labelUsername->setText(QString());
        userNameEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", nullptr));
        labelPassword->setText(QString());
        passwdEdit->setText(QString());
        passwdEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201(6-12\344\275\215)", nullptr));
        registerButton->setText(QCoreApplication::translate("LoginWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273    \345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H

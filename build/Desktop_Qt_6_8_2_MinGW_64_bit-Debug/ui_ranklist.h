/********************************************************************************
** Form generated from reading UI file 'ranklist.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANKLIST_H
#define UI_RANKLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_RankList
{
public:

    void setupUi(QFrame *RankList)
    {
        if (RankList->objectName().isEmpty())
            RankList->setObjectName("RankList");
        RankList->resize(320, 240);

        retranslateUi(RankList);

        QMetaObject::connectSlotsByName(RankList);
    } // setupUi

    void retranslateUi(QFrame *RankList)
    {
        RankList->setWindowTitle(QCoreApplication::translate("RankList", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RankList: public Ui_RankList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANKLIST_H

/********************************************************************************
** Form generated from reading UI file 'musicplayerr.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICPLAYERR_H
#define UI_MUSICPLAYERR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicPlayerr
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListWidget *musicList;
    QGroupBox *controlGroupBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *volumeLabel;
    QSlider *volumeSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *progressLabel;
    QSlider *progressSlider;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *prevBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *modeBtn;
    QPushButton *listBtn;
    QPushButton *openFile;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MusicPlayerr)
    {
        if (MusicPlayerr->objectName().isEmpty())
            MusicPlayerr->setObjectName("MusicPlayerr");
        MusicPlayerr->resize(657, 517);
        verticalLayout_2 = new QVBoxLayout(MusicPlayerr);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        groupBox = new QGroupBox(MusicPlayerr);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        musicList = new QListWidget(groupBox);
        musicList->setObjectName("musicList");

        gridLayout->addWidget(musicList, 0, 0, 1, 1);


        horizontalLayout_4->addWidget(groupBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        controlGroupBox = new QGroupBox(MusicPlayerr);
        controlGroupBox->setObjectName("controlGroupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlGroupBox->sizePolicy().hasHeightForWidth());
        controlGroupBox->setSizePolicy(sizePolicy);
        controlGroupBox->setMinimumSize(QSize(0, 180));
        controlGroupBox->setMaximumSize(QSize(16777215, 180));
        controlGroupBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        gridLayout_2 = new QGridLayout(controlGroupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, -1, 10, -1);
        volumeLabel = new QLabel(controlGroupBox);
        volumeLabel->setObjectName("volumeLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(volumeLabel->sizePolicy().hasHeightForWidth());
        volumeLabel->setSizePolicy(sizePolicy1);
        volumeLabel->setMinimumSize(QSize(60, 30));
        volumeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(volumeLabel);

        volumeSlider = new QSlider(controlGroupBox);
        volumeSlider->setObjectName("volumeSlider");
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setMinimumSize(QSize(350, 30));
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(volumeSlider);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        progressLabel = new QLabel(controlGroupBox);
        progressLabel->setObjectName("progressLabel");
        sizePolicy1.setHeightForWidth(progressLabel->sizePolicy().hasHeightForWidth());
        progressLabel->setSizePolicy(sizePolicy1);
        progressLabel->setMinimumSize(QSize(60, 30));
        progressLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(progressLabel);

        progressSlider = new QSlider(controlGroupBox);
        progressSlider->setObjectName("progressSlider");
        sizePolicy.setHeightForWidth(progressSlider->sizePolicy().hasHeightForWidth());
        progressSlider->setSizePolicy(sizePolicy);
        progressSlider->setMinimumSize(QSize(350, 30));
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_2->addWidget(progressSlider);


        verticalLayout->addLayout(horizontalLayout_2);

        widget = new QWidget(controlGroupBox);
        widget->setObjectName("widget");
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        prevBtn = new QPushButton(widget);
        prevBtn->setObjectName("prevBtn");
        sizePolicy1.setHeightForWidth(prevBtn->sizePolicy().hasHeightForWidth());
        prevBtn->setSizePolicy(sizePolicy1);
        prevBtn->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(prevBtn);

        playBtn = new QPushButton(widget);
        playBtn->setObjectName("playBtn");
        sizePolicy1.setHeightForWidth(playBtn->sizePolicy().hasHeightForWidth());
        playBtn->setSizePolicy(sizePolicy1);
        playBtn->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(playBtn);

        nextBtn = new QPushButton(widget);
        nextBtn->setObjectName("nextBtn");
        sizePolicy1.setHeightForWidth(nextBtn->sizePolicy().hasHeightForWidth());
        nextBtn->setSizePolicy(sizePolicy1);
        nextBtn->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(nextBtn);

        modeBtn = new QPushButton(widget);
        modeBtn->setObjectName("modeBtn");
        sizePolicy1.setHeightForWidth(modeBtn->sizePolicy().hasHeightForWidth());
        modeBtn->setSizePolicy(sizePolicy1);
        modeBtn->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(modeBtn);

        listBtn = new QPushButton(widget);
        listBtn->setObjectName("listBtn");
        sizePolicy1.setHeightForWidth(listBtn->sizePolicy().hasHeightForWidth());
        listBtn->setSizePolicy(sizePolicy1);
        listBtn->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(listBtn);

        openFile = new QPushButton(widget);
        openFile->setObjectName("openFile");
        sizePolicy1.setHeightForWidth(openFile->sizePolicy().hasHeightForWidth());
        openFile->setSizePolicy(sizePolicy1);
        openFile->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(openFile);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(controlGroupBox);


        retranslateUi(MusicPlayerr);

        QMetaObject::connectSlotsByName(MusicPlayerr);
    } // setupUi

    void retranslateUi(QWidget *MusicPlayerr)
    {
        MusicPlayerr->setWindowTitle(QCoreApplication::translate("MusicPlayerr", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MusicPlayerr", "\346\222\255\346\224\276\345\210\227\350\241\250", nullptr));
        controlGroupBox->setTitle(QCoreApplication::translate("MusicPlayerr", "\346\216\247\345\210\266", nullptr));
        volumeLabel->setText(QCoreApplication::translate("MusicPlayerr", "\351\237\263\351\207\217", nullptr));
        progressLabel->setText(QCoreApplication::translate("MusicPlayerr", "--:--", nullptr));
        prevBtn->setText(QString());
        playBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        listBtn->setText(QString());
        openFile->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicPlayerr: public Ui_MusicPlayerr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICPLAYERR_H

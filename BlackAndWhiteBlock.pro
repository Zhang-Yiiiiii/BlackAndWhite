QT       += core gui
QT       += network



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += multimedia multimediawidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractgamescene.cpp \
    animator.cpp \
    antgame.cpp \
    avatarwidget.cpp \
    basewindow.cpp \
    buildmapdialog.cpp \
    data.cpp \
    fancybaseplate.cpp \
    gamehelpdialog.cpp \
    gridbutton.cpp \
    hexagon.cpp \
    lightoutgame.cpp \
    loginwindow.cpp \
    main.cpp \
    mainscene.cpp \
    musicplayer.cpp \
    musicplayerr.cpp \
    mypushbutton.cpp \
    onlinewindow.cpp \
    overlay.cpp \
    ranklist.cpp \
    user.cpp \
    usermanager.cpp \
    userutils.cpp

HEADERS += \
    MessageTip.h \
    abstractgamescene.h \
    animator.h \
    antgame.h \
    avatarwidget.h \
    basewindow.h \
    buildmapdialog.h \
    config.h \
    data.h \
    fancybaseplate.h \
    gamehelpdialog.h \
    gridbutton.h \
    hexagon.h \
    lightoutgame.h \
    loginwindow.h \
    mainscene.h \
    musicplayer.h \
    musicplayerr.h \
    mypushbutton.h \
    onlinewindow.h \
    overlay.h \
    ranklist.h \
    user.h \
    usermanager.h \
    userutils.h

FORMS += \
    basewindow.ui \
    buildmapdialog.ui \
    loginwindow.ui \
    mainscene.ui \
    musicplayerr.ui \
    onlinewindow.ui \
    ranklist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=

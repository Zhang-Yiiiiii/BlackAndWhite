QT += core gui widgets multimedia multimediawidgets network

TARGET = BlackAndWhiteBlock
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    abstractgamescene.cpp \
    animator.cpp \
    antgame.cpp \
    avatarwidget.cpp \
    basewindow.cpp \
    buildmapdialog.cpp \
    chatdialog.cpp \
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
    chatdialog.h \
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
    chatdialog.ui \
    loginwindow.ui \
    mainscene.ui \
    musicplayerr.ui \
    onlinewindow.ui \
    ranklist.ui

RESOURCES += \
    res.qrc

# ========== 修复部分开始 ==========

# 设置库路径变量 - 使用更简单的路径，避免空格和特殊字符
win32 {
    CMARK_DIR = C:/cmark/cmark-gfm-0.29.0.gfm.13/build/install

    INCLUDEPATH += "$$CMARK_DIR/include"
    LIBS += -L"$$CMARK_DIR/lib" -lcmark-gfm

    message("CMARK include path: $$CMARK_DIR/include")
    message("CMARK library path: $$CMARK_DIR/lib")

    CMARK_DLL = $$CMARK_DIR/bin/libcmark-gfm.dll
    CMARK_DLL_DEST = $$OUT_PWD/libcmark-gfm.dll



    #QMAKE_POST_LINK += $$quote(cmd /c if exist \"$$CMARK_DLL\" copy /Y \"$$CMARK_DLL\" \"$$CMARK_DLL_DEST\")
}

# 链接库文件
LIBS += -lcmark-gfm -lcmark-gfm-extensions

# 添加数学库（可能需要）
LIBS += -lm

# 确保使用C++17标准
CONFIG += c++17

# ========== 修复部分结束 ==========

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

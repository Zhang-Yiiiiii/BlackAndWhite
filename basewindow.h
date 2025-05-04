#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QPixmap>
#include <QPainter>

#include "config.h"

namespace Ui
{
    class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

    void paintEvent(QPaintEvent* event) override;

protected:
    QPixmap m_background;
    QMenuBar* m_menubar;

    QMenu* m_startMenu;   //开始菜单
    QMenu* m_gameMenu;    //游戏菜单
    QMenu* m_toolMenu;    //工具菜单

    QAction* m_instructionAction;     //说明菜单项
    QAction* m_quitAction;            //退出游戏菜单项

protected slots:

    //显示游戏说明
    void onShowRule();

private:
    Ui::BaseWindow* ui;
};

#endif // BASEWINDOW_H

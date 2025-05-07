#ifndef BASEWINDOW_H
#define BASEWINDOW_H

/*
 * class: BaseWindow （基窗口类）
 *
 * 用处: 用于建立窗口框架、统一风格
 */

#include <QMainWindow>
#include <QMenuBar>
#include <QPixmap>
#include <QPainter>

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

    virtual void paintEvent(QPaintEvent*) override;

protected:
    QPixmap m_background;
    QMenuBar* m_menubar;    //菜单栏

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

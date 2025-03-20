#ifndef ONLINEWINDOW_H
#define ONLINEWINDOW_H

#include <QMainWindow>
#include "config.h"

namespace Ui
{
    class OnlineWindow;
}

class OnlineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OnlineWindow(QWidget *parent = nullptr);
    ~OnlineWindow();

private:
    Ui::OnlineWindow* ui;
};

#endif // ONLINEWINDOW_H

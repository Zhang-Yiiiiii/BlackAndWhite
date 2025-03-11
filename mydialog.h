#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui {
class myDialog;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myDialog(QWidget *parent = nullptr);

    //获取信息
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;

    ~myDialog();

signals:
    void getedInfo();

private slots:
    void confirmButtonClicked();


private:
    Ui::myDialog *ui;
};

#endif // MYDIALOG_H

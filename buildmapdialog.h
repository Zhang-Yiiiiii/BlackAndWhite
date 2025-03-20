#ifndef BUILDMAPDIALOG_H
#define BUILDMAPDIALOG_H

/*
 * class: Mydialog （我的对话框）
 *
 * 用处: 获取用户自建地图时的信息
 */

#include <QDialog>
#include <QString>
#include <QMessageBox>

namespace Ui
{
    class BuildMapDialog;
}

class BuildMapDialog : public QDialog
{
    Q_OBJECT

public:
    //构造和析构
    explicit BuildMapDialog(QWidget *parent = nullptr);
    ~BuildMapDialog();

    //获取信息
    int getNum1();
    int getNum2();
    int getNum3();
    int getNum4();
    int getNum5();

private:
    //信息
    int m_num1;
    int m_num2;
    int m_num3;
    int m_num4;
    int m_num5;

signals:
    void getedInfo();

private slots:
    void onConfirmButtonClicked();

private:
    Ui::BuildMapDialog* ui;
};

#endif // BUILDMAPDIALOG_H

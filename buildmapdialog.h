#ifndef BUILDMAPDIALOG_H
#define BUILDMAPDIALOG_H

/*****************************************************************
 * class: BuildMapDialog （建图对话框）
 *
 * 用处: 获取用户自建地图时的信息
 *****************************************************************/

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

    //------------------------构造析构----------------------------------

    explicit BuildMapDialog(QWidget *parent = nullptr);
    ~BuildMapDialog();

    //------------------------公有方法----------------------------------

    //获取信息
    int getNum1();
    int getNum2();
    int getNum3();
    int getNum4();
    int getNum5();

private:

    //------------------------私有属性----------------------------------

    //信息
    int m_num1;
    int m_num2;
    int m_num3;
    int m_num4;
    int m_num5;

signals:
    //------------------------信号----------------------------------

    void getedInfo();

private slots:
    //------------------------私有槽----------------------------------

    void onConfirmButtonClicked();

private:
    Ui::BuildMapDialog* ui;
};

#endif // BUILDMAPDIALOG_H

#ifndef RANKLIST_H
#define RANKLIST_H

#include <QFrame>
#include <QListView>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QListWidget>
#include <QVector>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>


namespace Ui {
class RankList;
}

class RankList : public QFrame
{
    Q_OBJECT

public:
    explicit RankList(QVector<std::pair<QString,int>> &,QWidget *parent = nullptr);

    //榜单排行
    QVector<std::pair<QString,int>> vRankList;

    ~RankList();

private:
    Ui::RankList *ui;
};

#endif // RANKLIST_H

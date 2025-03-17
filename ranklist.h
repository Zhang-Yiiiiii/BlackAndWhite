#ifndef RANKLIST_H
#define RANKLIST_H

/*
 * class: RankList （排行榜）
 *
 * 用处: 显示排行榜
 *
 */

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
    //构造和析构
    explicit RankList(QVector<std::pair<QString,int>> &,QWidget *parent = nullptr);
    ~RankList();

private:
    //榜单排行
    QVector<std::pair<QString,int>> m_vRankList;



private:
    Ui::RankList *ui;
};

#endif // RANKLIST_H

#include "ranklist.h"
#include "ui_ranklist.h"

RankList::RankList(QVector<std::pair<QString,int>> &v,QWidget *parent)
    : QFrame(parent), vRankList(v)
    , ui(new Ui::RankList)
{
    ui->setupUi(this);

    // 创建一个关闭按钮
    QPushButton *closeButton = new QPushButton("×", this);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    // 创建一个水平布局用于标题栏
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(closeButton);
    titleLayout->setContentsMargins(0, 0, 0, 0); // 设置标题栏布局的边距为0

    // 创建一个滚动区域
    QScrollArea *scrollArea = new QScrollArea(this);

    // 创建一个列表部件，用于显示排行榜的内容
    QListWidget *listWidget = new QListWidget(this);

    // 添加用户至榜单
    int ranking = 1;
    for(auto i : vRankList)
    {
        QString name = i.first;
        int time = i.second;

        QString str  = QString("%1  %2  %3").arg(QString::number(ranking)).arg(name).arg(time);

        listWidget->addItem(str);
    }

    // 将列表部件添加到滚动区域
    scrollArea->setWidget(listWidget);
    scrollArea->setWidgetResizable(true);

    // 创建一个垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 将滚动区域添加到布局
    layout->addLayout(titleLayout);
    layout->addWidget(scrollArea);
    layout->setContentsMargins(0, 0, 0, 0); // 设置主布局的边距为0

    // 设置排行榜窗口的布局
    setLayout(layout);

}

RankList::~RankList()
{
    delete ui;
}

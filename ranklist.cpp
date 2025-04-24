#include "ranklist.h"
#include "ui_ranklist.h"

RankList::RankList(QVector<std::pair<QString, int>> &v, QWidget *parent)
    : QFrame(parent), m_vRankList(v)
    , ui(new Ui::RankList)
{
    ui->setupUi(this);

    // 创建一个关闭按钮
    QPushButton *closeButton = new QPushButton("×");
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    // 创建一个水平布局用于标题栏
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(closeButton);
    titleLayout->setContentsMargins(0, 0, 0, 0); // 设置标题栏布局的边距为0

    // 创建一个滚动区域
    QScrollArea *scrollArea = new QScrollArea(this);

    // 创建 QTableWidget
    QTableWidget *tableWidget = new QTableWidget(m_vRankList.size(), 3); // 3 列：排名、名字、时间
    tableWidget->setHorizontalHeaderLabels({"Rank", "Name", "Time"}); // 设置表头

    // 设置表格属性
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    tableWidget->setSelectionMode(QAbstractItemView::NoSelection);   // 禁止选择
    tableWidget->verticalHeader()->setVisible(false);               // 隐藏垂直表头
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应列宽

    // 添加用户至榜单
    int ranking = 0;
    int row = 0;
    int last = -2;   //记录上一名的成绩
    for (const auto &i : m_vRankList)
    {
        QString name = i.first;
        int time = i.second;

        if (time == -1) continue; // 用户没有通关游戏

        if(last != time)  //分数与上一名不同
        {
            ranking++;
            last = time;
        }

        int secs = time % 60;
        int mins = (time / 60) % 60;
        int hours = time / 3600;

        // 设置排名
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(ranking)));

        // 设置名字
        tableWidget->setItem(row, 1, new QTableWidgetItem(name));

        // 设置时间
        tableWidget->setItem(row, 2, new QTableWidgetItem(
                                 QString("%1:%2:%3")
                                 .arg(hours, 2, 10, QLatin1Char('0'))
                                 .arg(mins, 2, 10, QLatin1Char('0'))
                                 .arg(secs, 2, 10, QLatin1Char('0'))));

        row++;
    }

    // 将 QTableWidget 添加到滚动区域
    scrollArea->setWidget(tableWidget);
    scrollArea->setWidgetResizable(true); // 允许 QTableWidget 自适应大小

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

#include "basewindow.h"
#include "ui_basewindow.h"
#include "config.h"

#include <fstream>
#include <sstream>
#include <QMessageBox>

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH, BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);
    this->setWindowIcon(QIcon(MYICON));
    this->m_background.load(BACKGROUDPATH);     //提前加载背景图片
    this->setAttribute(Qt::WA_DeleteOnClose);   //设置自动释放内存

    //设置菜单栏
    m_menubar = menuBar();
    m_menubar->setParent(this);
    m_menubar->setStyleSheet("font: 700 12pt \"Microsoft YaHei UI\"; background-color: rgba(217, 217, 217, 150); color: rgb(66, 66, 66);");

    //设置菜单
    m_startMenu = m_menubar->addMenu("开始");
    m_gameMenu = m_menubar->addMenu("游戏");
    m_toolMenu = m_menubar->addMenu("工具");

    //设置菜单项
    //游戏说明
    m_instructionAction = m_gameMenu->addAction("说明");
    connect(m_instructionAction, &QAction::triggered, this, &BaseWindow::onShowRule);

    //退出游戏
    m_quitAction = m_startMenu->addAction("退出游戏");
    connect(m_quitAction, &QAction::triggered, [ = ]()
    {
        exit(0);
    });
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿
    painter.drawPixmap(0, 0, m_background);
}

//显示游戏说明
void BaseWindow::onShowRule()
{
    std::ifstream ifs(RULEPATH);

    // 打开文件
    if (!ifs.is_open())
    {
        QMessageBox::about(this, "通知", QString("无法打开文件").arg(RULEPATH));
        return;
    }

    // 使用 std::stringstream 读取整个文件内容
    std::stringstream buffer;
    buffer << ifs.rdbuf(); // 将文件内容读取到 stringstream 中

    //关闭文件
    ifs.close();

    // 将 stringstream 的内容转换为 QString
    QString fileContent = QString::fromStdString(buffer.str());

    QMessageBox::about(this, "说明", fileContent);
}

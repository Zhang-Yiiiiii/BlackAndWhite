#include "basewindow.h"
#include "ui_basewindow.h"
#include "config.h"

#include <fstream>
#include <sstream>
#include <QMessageBox>

//----------------------------------构造析构--------------------------------------------

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    //设置窗口大小 标题 图标
    this->setFixedSize(BACKGROUDWIDTH, BACKGROUDHEIGHT);
    this->setWindowTitle(MYTITLE);              //设置标题
    this->setWindowIcon(QIcon(MYICON));         //设置图标
    this->m_background.load(BACKGROUDPATH);     //提前加载背景图片

    //设置菜单栏
    m_menubar = menuBar();
    m_menubar->setParent(this);
    m_menubar->setStyleSheet("font: 700 12pt \"Microsoft YaHei UI\"; background-color: rgba(255, 255, 255, 80); color: black;");

    //设置菜单
    m_startMenu = m_menubar->addMenu("开始");
    m_gameMenu = m_menubar->addMenu("游戏");
    m_toolMenu = m_menubar->addMenu("工具");

    //设置菜单项
    //游戏帮助
    m_rule = m_menubar->addMenu("帮助");

    QAction* gameHelpAction = m_rule->addAction("游戏帮助");
    gameHelpAction->setIcon(QIcon(INTRODUCTIONICONPATH));

    m_gameHelpDia = new GameHelpDialog(this);
    connect(gameHelpAction, &QAction::triggered, m_gameHelpDia, &QDialog::show);

    // m_antRule = m_rule->addAction("兰顿蚂蚁");
    // m_lightOutRule = m_rule->addAction("熄灯游戏");

    // connect(m_antRule, &QAction::triggered, this, &BaseWindow::onShowAntRule);
    // connect(m_lightOutRule, &QAction::triggered, this, &BaseWindow::onShowLightOutRule);

    //退出游戏
    m_quitAction = m_startMenu->addAction("退出游戏");
    m_quitAction->setIcon(QIcon(QUITICONPATH));
    connect(m_quitAction, &QAction::triggered, [ = ]()
    {
        exit(0);
    });
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

//----------------------------------公共方法--------------------------------------------

//设置音乐播放器
void BaseWindow::setMusicPlayer(MusicPlayer *musicPlayer)
{
    //设置菜单
    m_quitAction = m_menubar->addAction("音乐");
    m_musicPlayer = musicPlayer;
    connect(m_quitAction, &QAction::triggered, m_musicPlayer, &QWidget::show);
}

//----------------------------------保护方法--------------------------------------------

void BaseWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    painter.drawPixmap(0, 0, m_background);
}

//----------------------------------保护槽--------------------------------------------

//显示兰顿蚂蚁游戏说明
void BaseWindow::onShowAntRule()
{
    std::ifstream ifs(ANTGAMERULE);

    // 打开文件
    if (!ifs.is_open())
    {
        QMessageBox::about(this, "通知", QString("无法打开文件").arg(ANTGAMERULE));
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

//显示熄灯游戏说明
void BaseWindow::onShowLightOutRule()
{
    std::ifstream ifs(LIGHTOUTRULE);

    // 打开文件
    if (!ifs.is_open())
    {
        QMessageBox::about(this, "通知", QString("无法打开文件").arg(LIGHTOUTRULE));
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

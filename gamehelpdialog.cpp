#include "gamehelpdialog.h"

#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QTextBrowser>

void setMarkdownStyled(QTextBrowser* browser, const QString& markdown)
{
    //创建一个临时 QTextDocument 用于 Markdown 转换
    QTextDocument* doc = new QTextDocument(browser);  // 父对象设为 browser，自动管理内存
    doc->setMarkdown(markdown);

    //生成 HTML 并注入 CSS 样式
    QString html = doc->toHtml();
    QString css = R"(
            h1 { font-size: 20px; font-weight: bold; margin-top: 20px; margin-bottom: 10px; }
            h2 { font-size: 16px; font-weight: bold; margin-top: 16px; margin-bottom: 8px; }
            h3 { font-size: 14px; font-weight: bold; margin-top: 12px; margin-bottom: 6px; }
            p  { font-size: 14px; margin: 8px 0; line-height: 1.6; }
            ul, ol { margin-left: 20px; font-size: 14px; }
            img { max-width: 100%; }
        )";
    html.replace("<head>", "<head><style>" + css + "</style>");

    //设置新文档
    doc->setHtml(html);
    browser->setDocument(doc);  // 用新文档替换旧文档
}

GameHelpDialog::GameHelpDialog(QWidget* parent) : QDialog(parent), m_currentPage(0)
{
    // 在 GameHelpDialog 构造函数中添加这段代码（或统一封装为 setStyleSheet 方法）
    QString style = R"(
        QPushButton {
            background-color: #2980b9;
            color: white;
            border-radius: 6px;
            padding: 6px 12px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #3498db;
        }

        QPushButton:disabled {
            background-color: #ccc;
            color: #666;
        }
    )";
    this->setStyleSheet(style);

    setWindowTitle("游戏说明");
    resize(600, 400);

    m_markdownFiles << ":/rule/lightoutGameRule.md" << ":/rule/antGameRule.md";  // 使用资源文件路径

    m_browser = new QTextBrowser(this);
    m_browser->setReadOnly(true);

    m_prevButton = new QPushButton("上一页", this);
    m_nextButton = new QPushButton("下一页", this);

    connect(m_prevButton, &QPushButton::clicked, this, &GameHelpDialog::showPrevious);
    connect(m_nextButton, &QPushButton::clicked, this, &GameHelpDialog::showNext);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_prevButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_nextButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_browser);
    mainLayout->addLayout(buttonLayout);

    loadPage(m_currentPage);
}

void GameHelpDialog::showPrevious()
{
    if (m_currentPage > 0)
    {
        m_currentPage--;
        loadPage(m_currentPage);
    }
}

void GameHelpDialog::showNext()
{
    if (m_currentPage < m_markdownFiles.size() - 1)
    {
        m_currentPage++;
        loadPage(m_currentPage);
    }
}

void GameHelpDialog::loadPage(int index)
{
    if (index < 0 || index >= m_markdownFiles.size())
    {
        return;
    }

    QFile file(m_markdownFiles[index]);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString markdown = QTextStream(&file).readAll();
        m_browser->document()->setMarkdown(markdown);

        // QString markdown = QTextStream(&file).readAll();
        // setMarkdownStyled(m_browser, markdown);
    }

    file.close();

    // 设置按钮状态
    m_prevButton->setEnabled(index > 0);
    m_nextButton->setEnabled(index < m_markdownFiles.size() - 1);

    // 设置窗口标题（例如：游戏说明（1/2））
    setWindowTitle(QString("游戏说明（%1/%2）").arg(index + 1).arg(m_markdownFiles.size()));
}

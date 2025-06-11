#include "chatdialog.h"
#include "MessageTip.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QDebug>
#include <QTimer>
#include <QTextDocument>
#include <QScrollBar>
#include <QRegularExpression>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QFileInfo>

//对话文件
const QString CONTEXT_FILE = "conversation_context.json";

//------------------------构造和析构----------------------------------
ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent),
      currentReply(nullptr)
{
    setWindowTitle("DeepSeek AI");
    resize(450, 800);

    setupUI();

    loadContext();

    //默认对话
    chatDisplay->append("<b style='color: #27ae60;'>AI:</b> " +
                        markdownToHtml("你好！我是DeepSeek AI助手，我支持markdown语法"));
}

ChatDialog::~ChatDialog()
{
    qDebug() << "Destructor: " << this;

    if (currentReply)
    {
        currentReply->abort();
        delete currentReply;
        currentReply = nullptr;
    }
}

//------------------------私有方法----------------------------------
//转Html
QString ChatDialog::markdownToHtml(const QString &markdown)
{
    QString html = markdown;

    // 改进的公式处理
    // 块级公式处理 ($$...$$)
    static QRegularExpression blockLatexRegex("\\$\\$(.*?)\\$\\$",
            QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator blockIter = blockLatexRegex.globalMatch(html);

    while (blockIter.hasNext())
    {
        QRegularExpressionMatch match = blockIter.next();
        QString latex = match.captured(1).trimmed();
        QString encoded = QUrl::toPercentEncoding(latex);

        // 使用多个服务作为备选
        QStringList services =
        {
            "https://latex.codecogs.com/svg.latex?\\dpi{150}%20%1",
            "https://math.vercel.app/?from=%1",
            "https://tex.s2cms.ru/svg/%1"
        };

        QString sources;

        for (const QString &service : services)
        {
            sources += QString("\"%1\", ").arg(service.arg(encoded));
        }

        sources.chop(2); // 移除最后的逗号和空格

        QString imgTag = QString(
                             "<div class=\"latex-block\" style=\"text-align:center; margin:15px 0;\">"
                             "<img src=\"%1\" "
                             "srcset=\"%2\" "
                             "alt=\"%3\" "
                             "style=\"max-width:100%%; background:white; padding:10px; border-radius:5px;\" "
                             "onerror=\"this.onerror=null; this.style.color='white'; this.style.backgroundColor='transparent'; this.style.padding='5px'; this.innerHTML='LaTeX渲染失败: ' + this.alt;\">"
                             "</div>")
                         .arg(services.first().arg(encoded), sources, latex.toHtmlEscaped());

        html.replace(match.captured(0), imgTag);
    }

    // 行内公式处理 ($...$)
    static QRegularExpression inlineLatexRegex("\\$(.*?)\\$",
            QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator inlineIter = inlineLatexRegex.globalMatch(html);

    while (inlineIter.hasNext())
    {
        QRegularExpressionMatch match = inlineIter.next();
        QString latex = match.captured(1).trimmed();
        QString encoded = QUrl::toPercentEncoding(latex);

        QStringList services =
        {
            "https://latex.codecogs.com/svg.latex?\\inline%20%1",
            "https://math.vercel.app/?from=%1",
            "https://tex.s2cms.ru/svg/%1"
        };

        QString sources;

        for (const QString &service : services)
        {
            sources += QString("\"%1\", ").arg(service.arg(encoded));
        }

        sources.chop(2);

        QString imgTag = QString(
                             "<img src=\"%1\" "
                             "srcset=\"%2\" "
                             "alt=\"%3\" "
                             "style=\"vertical-align:middle; display:inline-block; background:white; padding:3px; border-radius:3px;\" "
                             "onerror=\"this.onerror=null; this.style.color='white'; this.style.backgroundColor='transparent'; this.style.padding='2px'; this.innerHTML='LaTeX渲染失败: ' + this.alt;\">")
                         .arg(services.first().arg(encoded), sources, latex.toHtmlEscaped());

        html.replace(match.captured(0), imgTag);
    }

    // // 1. 代码块处理 (```code```)
    // static QRegularExpression codeBlockRegex("```(.*?)```",
    // QRegularExpression::DotMatchesEverythingOption | QRegularExpression::MultilineOption);
    // QRegularExpressionMatchIterator i = codeBlockRegex.globalMatch(html);

    // while (i.hasNext())
    // {
    // QRegularExpressionMatch match = i.next();
    // QString code = match.captured(1);
    // code.replace("<", "&lt;").replace(">", "&gt;");
    // html.replace(match.captured(0), "<pre>" + code + "</pre>");
    // }

    // // 2. 内联代码 (`code`)
    // static QRegularExpression inlineCodeRegex("`([^`]+)`");
    // html.replace(inlineCodeRegex, "<code>\\1</code>");

    // 3. 粗体 (**bold**)
    static QRegularExpression boldRegex("\\*\\*(.+?)\\*\\*");
    html.replace(boldRegex, "<b>\\1</b>");

    // 4. 斜体 (*italic*)
    static QRegularExpression italicRegex("\\*(.+?)\\*");
    html.replace(italicRegex, "<i>\\1</i>");

    // 5. 链接 ()
    static QRegularExpression linkRegex("\\[([^\\]]+)\\]\\(([^\\)]+)\\)");
    html.replace(linkRegex, "<a href=\"\\2\">\\1</a>");

    // 6. 图片 ()
    static QRegularExpression imageRegex("!\\[([^\\]]*)\\]\\(([^\\)]+)\\)");
    html.replace(imageRegex, "<img src=\"\\2\" alt=\"\\1\" style=\"max-width:100%;\">");

    // 7. 标题 (#, ##, ###)
    html.replace(QRegularExpression("^#\\s+(.+)$", QRegularExpression::MultilineOption), "<h1>\\1</h1>");
    html.replace(QRegularExpression("^##\\s+(.+)$", QRegularExpression::MultilineOption), "<h2>\\1</h2>");
    html.replace(QRegularExpression("^###\\s+(.+)$", QRegularExpression::MultilineOption), "<h3>\\1</h3>");
    html.replace(QRegularExpression("^####\\s+(.+)$", QRegularExpression::MultilineOption), "<h4>\\1</h3>");

    // 8. 无序列表 -
    static QRegularExpression ulRegex("^([*+-])\\s+(.+)$", QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator ulIterator = ulRegex.globalMatch(html);
    QStringList ulLines;

    while (ulIterator.hasNext())
    {
        QRegularExpressionMatch match = ulIterator.next();
        ulLines << "<li>" + match.captured(2) + "</li>";
    }

    if (!ulLines.isEmpty())
    {
        html.replace(ulRegex, "");
        html.prepend("<ul>" + ulLines.join("") + "</ul>");
    }

    // 9. 有序列表 - 改进处理
    static QRegularExpression olRegex("^(\\d+)\\.\\s+(.+)$", QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator olIterator = olRegex.globalMatch(html);
    QStringList olLines;

    while (olIterator.hasNext())
    {
        QRegularExpressionMatch match = olIterator.next();
        olLines << "<li>" + match.captured(2) + "</li>";
    }

    if (!olLines.isEmpty())
    {
        html.replace(olRegex, "");
        html.prepend("<ol>" + olLines.join("") + "</ol>");
    }

    // 10. 引用块 (>)
    static QRegularExpression blockquoteRegex("^>\\s+(.+)$", QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator bqIterator = blockquoteRegex.globalMatch(html);
    QStringList bqLines;

    while (bqIterator.hasNext())
    {
        QRegularExpressionMatch match = bqIterator.next();
        bqLines << "<p>" + match.captured(1) + "</p>";
    }

    if (!bqLines.isEmpty())
    {
        html.replace(blockquoteRegex, "");
        html.prepend("<blockquote style=\"border-left: 3px solid #ccc; padding-left: 10px; margin: 10px 0;\">" +
                     bqLines.join("") + "</blockquote>");
    }

    // 11. 表格处理（简单表格）
    static QRegularExpression tableRegex("\\|(.+)\\|\\n\\|([-:|]+)\\|\\n((?:\\|.+\\|\\n?)+)");
    QRegularExpressionMatch tableMatch = tableRegex.match(html);

    if (tableMatch.hasMatch())
    {
        QString headers = tableMatch.captured(1);
        QString align = tableMatch.captured(2);
        QString rows = tableMatch.captured(3);

        QStringList headerList = headers.split("|", Qt::SkipEmptyParts);
        QStringList alignList = align.split("|", Qt::SkipEmptyParts);
        QStringList rowLines = rows.split("\n", Qt::SkipEmptyParts);

        QString tableHtml = "<table style=\"border-collapse: collapse; width: 100%; margin: 15px 0;\">";

        tableHtml += "<thead><tr>";

        for (int i = 0; i < headerList.size(); i++)
        {
            QString style = "text-align: left; padding: 8px; border-bottom: 1px solid #ddd;";

            if (alignList.size() > i)
            {
                if (alignList[i].contains(":-:"))
                {
                    style = "text-align: center;" + style;
                }
                else if (alignList[i].contains("-:"))
                {
                    style = "text-align: right;" + style;
                }
            }

            tableHtml += QString("<th style=\"%1\">%2</th>").arg(style).arg(headerList[i].trimmed());
        }

        tableHtml += "</tr></thead>";

        tableHtml += "<tbody>";

        for (const QString &row : rowLines)
        {
            QStringList cols = row.split("|", Qt::SkipEmptyParts);

            if (cols.isEmpty())
            {
                continue;
            }

            tableHtml += "<tr>";

            for (const QString &col : cols)
            {
                tableHtml += QString("<td style=\"padding: 8px; border-bottom: 1px solid #ddd;\">%1</td>").arg(col.trimmed());
            }

            tableHtml += "</tr>";
        }

        tableHtml += "</tbody></table>";

        html.replace(tableMatch.captured(0), tableHtml);
    }

    // 12. 水平线 (---)
    html.replace(QRegularExpression("\\n-{3,}\\n"), "<hr style=\"border: 0; border-top: 1px solid #eee; margin: 20px 0;\">");

    // 13. 换行处理 - 保留段落结构
    html.replace("\n\n", "</p><p>");
    html.replace("\n", "<br>");
    html = "<p>" + html + "</p>";

    // 添加基本样式（改进公式样式）
    html = "<style>"
           "pre { background: #f5f5f5; padding: 10px; border-radius: 5px; overflow-x: auto; }"
           "code { background: #f5f5f5; padding: 2px 4px; border-radius: 3px; font-family: monospace; }"
           "img { max-width: 100%; display: block; margin: 10px 0; }"
           "h1 { font-size: 1.5em; margin: 15px 0; border-bottom: 1px solid #eee; padding-bottom: 5px; }"
           "h2 { font-size: 1.3em; margin: 13px 0; }"
           "h3 { font-size: 1.1em; margin: 11px 0; }"
           "ul, ol { margin: 10px 0 10px 25px; }"
           "li { margin: 5px 0; }"
           "p { margin: 10px 0; line-height: 1.5; }"
           "a { color: #1a73e8; text-decoration: none; }"
           "a:hover { text-decoration: underline; }"
           "blockquote { color: #555; }"
           "div.latex-block { text-align: center; margin: 15px 0; }"
           "img.latex-img { background: white; padding: 10px; border-radius: 5px; }"
           "img.latex-inline { background: white; padding: 2px; border-radius: 3px; vertical-align: middle; }"
           "</style>" +
           html;
    return html;
}

void ChatDialog::appendMessage(const QString &sender, const QString &msg)
{
    int scrollPos = chatDisplay->verticalScrollBar()->value();
    bool atBottom = scrollPos == chatDisplay->verticalScrollBar()->maximum();

    chatDisplay->moveCursor(QTextCursor::End);
    chatDisplay->textCursor().insertHtml("<hr style=\"border: 0; border-top: 1px solid #3a3a4a; margin: 15px 0;\">");

    QString headerStyle = "font-weight: bold; padding: 8px 0;";
    QString headerColor = (sender == "你:") ? "#6c5ce7" : "#27ae60";
    QString headerHtml = QString("<div style=\"%1 color: %2;\">%3</div>")
                         .arg(headerStyle, headerColor, sender);

    chatDisplay->moveCursor(QTextCursor::End);
    chatDisplay->textCursor().insertHtml(headerHtml);

    QString contentHtml;

    if (sender == "你:")
    {
        contentHtml = QString("<div style=\"padding: 8px 0; color: #e0e0e0;\">%1</div>")
                      .arg(msg.toHtmlEscaped());
    }
    else
    {
        contentHtml = markdownToHtml(msg);
    }

    chatDisplay->moveCursor(QTextCursor::End);
    chatDisplay->textCursor().insertHtml(contentHtml);

    chatDisplay->moveCursor(QTextCursor::End);
    chatDisplay->textCursor().insertHtml("<div style=\"height: 15px;\"></div>");

    if (atBottom)
    {
        QTimer::singleShot(0, [this]()
        {
            chatDisplay->verticalScrollBar()->setValue(chatDisplay->verticalScrollBar()->maximum());
        });
    }
    else
    {
        chatDisplay->verticalScrollBar()->setValue(scrollPos);
    }
}

void ChatDialog::onSendClicked()
{
    sendButton->setDisabled(true);  //设置不可按
    MessageTip::tipFromCenter(this, "请等待回答");

    QString text = chatDisplay->toPlainText().trimmed();

    if (text.isEmpty())
    {
        sendButton->setDisabled(false);  //设置可按
        return;
    }

    conversationHistory.append(qMakePair("user", text));

    QJsonArray messages;

    int startIdx = qMax(0, conversationHistory.size() - 5);

    for (int i = startIdx; i < conversationHistory.size(); i++)
    {
        const auto &entry = conversationHistory[i];
        QJsonObject message;
        message["role"] = entry.first;
        message["content"] = entry.second;
        messages.append(message);
    }

    QJsonObject systemMessage;
    systemMessage["role"] = "system";
    systemMessage["content"] = "你是一个乐于助人的助手。请保持对话连贯性。";
    messages.prepend(systemMessage);

    QJsonObject data;
    data["model"] = "gpt-3.5-turbo";
    data["messages"] = messages;
    data["max_tokens"] = 150;

    //QString userText = inputEdit->text().trimmed();
    QString userText = inputEdit->toPlainText();

    if (userText.isEmpty())
    {
        return;
    }

    appendMessage("你:", userText);
    inputEdit->clear();

    QUrl url("https://api.deepseek.com/v1/chat/completions");   //网址
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

    messages.append(QJsonObject{{"role", "user"}, {"content", userText}});

    QJsonObject rootJson;
    rootJson["model"] = "deepseek-chat";
    rootJson["messages"] = messages;
    rootJson["temperature"] = 0.7;
    rootJson["stream"] = false;

    QJsonDocument doc(rootJson);
    QByteArray jsonData = doc.toJson();

    if (currentReply)
    {
        currentReply->abort();
        currentReply->deleteLater();
        currentReply = nullptr;
    }

    currentReply = networkManager->post(request, jsonData);
    connect(currentReply, &QNetworkReply::finished, this, &ChatDialog::onNetworkReplyFinished);

    QTimer::singleShot(100000, [this]() //最长等待时间
    {
        if (currentReply && currentReply->isRunning())
        {
            appendMessage("系统:", "请求超时，请重试。");
            currentReply->abort();
            sendButton->setDisabled(false);
        }
    });

    saveContext();
}

void ChatDialog::onNetworkReplyFinished()
{
    sendButton->setDisabled(false);

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (!reply || reply != currentReply)
    {
        if (reply)
        {
            reply->deleteLater();
        }

        return;
    }

    reply->deleteLater();
    currentReply = nullptr;

    if (reply->error() == QNetworkReply::OperationCanceledError)
    {
        return;
    }

    if (reply->error() != QNetworkReply::NoError)
    {
        appendMessage("系统:", QString("请求失败: %1").arg(reply->errorString()));
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    if (!jsonDoc.isObject() || !jsonDoc.object().contains("choices"))
    {
        appendMessage("系统:", "API 返回格式异常");
        qDebug() << "API 返回异常:" << jsonDoc;
        return;
    }

    QJsonArray choices = jsonDoc.object()["choices"].toArray();

    if (choices.isEmpty())
    {
        appendMessage("系统:", "AI 未返回有效内容");
        return;
    }

    QString aiReply = choices[0].toObject()["message"].toObject()["content"].toString();

    if (aiReply.isEmpty())
    {
        appendMessage("系统", "AI 返回内容为空");
    }
    else
    {
        conversationHistory.append(qMakePair("assistant", aiReply));
        saveContext();
        appendMessage("AI", aiReply);
    }
}

void ChatDialog::onGetAidInfo(QString info)
{
    //inputEdit->setText(info);
    inputEdit->setPlainText(info);
}

void ChatDialog::saveContext()
{
    QFile file(CONTEXT_FILE);

    if (file.open(QIODevice::WriteOnly))
    {
        QJsonArray historyArray;

        for (const auto &entry : conversationHistory)
        {
            QJsonObject item;
            item["role"] = entry.first;
            item["content"] = entry.second;
            historyArray.append(item);
        }

        QJsonDocument doc(historyArray);
        file.write(doc.toJson());
        file.close();
    }
}

void ChatDialog::loadContext()
{
    QFile file(CONTEXT_FILE);

    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonArray historyArray = doc.array();

        conversationHistory.clear();

        for (const auto &item : historyArray)
        {
            QJsonObject obj = item.toObject();
            QString role = obj["role"].toString();
            QString content = obj["content"].toString();
            conversationHistory.append(qMakePair(role, content));
        }

        file.close();
    }
}

void ChatDialog::clearContext()
{
    conversationHistory.clear();
    QFile::remove(CONTEXT_FILE);
}

void ChatDialog::setupUI()
{
    setStyleSheet(R"(
        QDialog {
            background-color: #2d2d39;
            border-radius: 12px;
            font-family: 'Segoe UI', 'Microsoft YaHei', sans-serif;
        }
        QTextEdit, QLineEdit {
            background-color: #1e1e27;
            color: #e0e0e0;
            border: 1px solid #3a3a4a;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
        }
        QPushButton {
            background-color: #6c5ce7;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 8px 16px;
            font-weight: 500;
            min-width: 80px;
        }
        QPushButton:hover {
            background-color: #5d4fe0;
        }
        QPushButton:pressed {
            background-color: #4c3fd9;
        }
        QPushButton:disabled {
            background-color: #4a4a5a;
            color: #8a8a9a;
        }
        QScrollBar:vertical {
            border: none;
            background: #252531;
            width: 10px;
            margin: 0px 0px 0px 0px;
        }
        QScrollBar::handle:vertical {
            background: #4a4a5a;
            min-height: 20px;
            border-radius: 4px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
        }
    )");

    apiEdit = new QLineEdit(this);
    apiEdit->setPlaceholderText(tr("Deepseek API"));

    confirmApiBtn = new QPushButton(this);
    confirmApiBtn->setText("确定");

    connect(confirmApiBtn, &QPushButton::clicked, this, [this]()
    {
        apiKey = apiEdit->text();
        MessageTip::tipFromCenter(this, "设置成功");
    });

    QHBoxLayout *apiLayout = new QHBoxLayout;
    apiLayout->addWidget(apiEdit, 9);
    apiLayout->addWidget(confirmApiBtn, 1);

    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setAcceptRichText(true);
    chatDisplay->setTextInteractionFlags(Qt::TextBrowserInteraction);

    inputEdit = new QTextEdit(this);
    sendButton = new QPushButton("发送", this);
    aidButton = new QPushButton("求助", this);

    sendButton->setDefault(true);   //默认按钮

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(inputEdit, 9);
    inputLayout->addWidget(aidButton, 1);
    inputLayout->addWidget(sendButton, 1);

    inputEdit->setPlaceholderText(tr("Type your message here..."));
    inputEdit->setStyleSheet(R"(
        QLineEdit {
            background-color: #252531;
            padding: 12px;
            font-size: 14px;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(apiLayout, 1);
    mainLayout->addWidget(chatDisplay, 9);
    mainLayout->addLayout(inputLayout, 1);

    setLayout(mainLayout);

    networkManager = new QNetworkAccessManager(this);

    connect(sendButton, &QPushButton::clicked, this, &ChatDialog::onSendClicked);
    //connect(inputEdit, &QTextEdit::returnPressed, this, &ChatDialog::onSendClicked);
    connect(aidButton, &QPushButton::clicked, this, [this]()
    {
        emit applyAidInfo();
    });
}

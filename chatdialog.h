//sk-91a377a4bc0f4039b81babd086f7f1c5

#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QTextDocument>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QNetworkReply;

class ChatDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

    void onGetAidInfo(QString info);

private slots:
    void onSendClicked();
    void onNetworkReplyFinished();

private:
    // 将Markdown转换为HTML（仅用于AI回复）
    QString markdownToHtml(const QString &markdown);

    // 添加消息（用户消息保持纯文本）
    void appendMessage(const QString &sender, const QString &msg);

    QTextEdit* chatDisplay;
    QLineEdit* inputEdit;
    QPushButton* sendButton;
    QNetworkAccessManager* networkManager;
    QNetworkReply* currentReply;
    QPushButton* aidButton;
    QLineEdit* apiEdit;
    QPushButton* confirmApiBtn;

    // API密钥
    QString apiKey = "sk-91a377a4bc0f4039b81babd086f7f1c5";

    // 添加对话历史成员变量
    QList<QPair<QString, QString>> conversationHistory; // <角色, 内容>
    void saveContext(); // 保存上下文
    void loadContext(); // 加载上下文
    void clearContext(); // 清除上下文

signals:
    void applyAidInfo();
};

#endif // CHATDIALOG_H

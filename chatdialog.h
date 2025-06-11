#ifndef CHATDIALOG_H
#define CHATDIALOG_H

/*****************************************************************
 * class: ChatDialog （AI对话）
 *
 * 用处： 用于和AI对话、让AI帮助求解
 *
 ********************************************************************/

#include <QDialog>
#include <QNetworkAccessManager>
#include <QTextDocument>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QNetworkReply;

//API
//sk-91a377a4bc0f4039b81babd086f7f1c5

class ChatDialog : public QDialog
{
    Q_OBJECT
public:
    //------------------------构造和析构----------------------------------
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

    //获取游戏信息
    void onGetAidInfo(QString info);

private:

    //------------------------私有方法----------------------------------

    // 将Markdown转换为HTML（仅用于AI回复）
    QString markdownToHtml(const QString &markdown);

    // 添加消息（用户消息保持纯文本）
    void appendMessage(const QString &sender, const QString &msg);

    // 添加对话历史成员变量
    QList<QPair<QString, QString>> conversationHistory; // <角色, 内容>
    void saveContext(); // 保存上下文
    void loadContext(); // 加载上下文
    void clearContext(); // 清除上下文

    //设置UI
    void setupUI();

    //------------------------私有属性----------------------------------

    //UI组件
    QTextEdit* chatDisplay;
    QTextEdit* inputEdit;
    QPushButton* sendButton;
    QNetworkAccessManager* networkManager;
    QNetworkReply* currentReply;
    QPushButton* aidButton;
    QLineEdit* apiEdit;
    QPushButton* confirmApiBtn;

    // API密钥
    QString apiKey = "sk-91a377a4bc0f4039b81babd086f7f1c5";

private slots:

    //------------------------私有槽----------------------------------

    void onSendClicked();
    void onNetworkReplyFinished();

signals:
    void applyAidInfo();
};

#endif // CHATDIALOG_H

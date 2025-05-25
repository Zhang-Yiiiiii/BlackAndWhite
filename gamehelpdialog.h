#ifndef GAMEHELPDIALOG_H
#define GAMEHELPDIALOG_H

#include <QDialog>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

class GameHelpDialog : public QDialog
{
    Q_OBJECT

public:
    GameHelpDialog(QWidget* parent = nullptr);

private slots:
    void showPrevious();
    void showNext();

private:
    void loadPage(int index);

    QTextBrowser* m_browser;
    QPushButton* m_prevButton;
    QPushButton* m_nextButton;

    QStringList m_markdownFiles; // 存储文件路径
    int m_currentPage;
};

#endif // GAMEHELPDIALOG_H

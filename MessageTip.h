#ifndef MESSAGETIP_H
#define MESSAGETIP_H

#include <QString>
#include <QToolTip>
#include <QWidget>

/*****************************************************************
 * class: MessageTip （消息提示）
 *
 * 用处: 显示提示消息
 *****************************************************************/

class MessageTip
{
public:
    static void tipFromBottom(QWidget * ob, QString message)
    {
        if(!ob)
        {
            return ;
        }

        // 获取当前字体下文本的渲染宽度
        QToolTip::setFont(QFont("Arial", 10));  // 确保字体有效
        QFontMetrics metrics(QToolTip::font());
        int textWidth = metrics.horizontalAdvance(message);

        QPoint pos = QPoint(ob->width() / 2 - textWidth / 2, ob->rect().bottom() + 3);
        QToolTip::showText(ob->mapToGlobal(pos), message);
    }

    static void tipFromCenter(QWidget* ob, QString message)
    {
        if(!ob)
        {
            return ;
        }

        // 获取当前字体下文本的渲染宽度
        QToolTip::setFont(QFont("Arial", 10));  // 确保字体有效
        QFontMetrics metrics(QToolTip::font());
        int textWidth = metrics.horizontalAdvance(message);

        QPoint pos = QPoint(ob->width() / 2 - textWidth / 2, ob->height() / 2);
        QToolTip::showText(ob->mapToGlobal(pos), message);
    }
};

#endif // MESSAGETIP_H

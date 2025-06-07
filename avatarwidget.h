// avatarwidget.h
#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>
#include <QString>

#include "user.h"

class AvatarWidget : public QWidget
{
    Q_OBJECT

public:
    AvatarWidget(User* user, QWidget* parent = nullptr);
    QSize sizeHint() const override;

    void setUser(User* user);
    void setUsername(bool isDefault = 0);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent * event) override;

private:
    void updateAvatar(const QString& path);
    User* m_user;
    QPixmap m_pixmap;

    QLabel* avatar;
    QLabel* nameLabel;

    void initUi();
};

#endif // AVATARWIDGET_H

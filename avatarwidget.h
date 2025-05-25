// avatarwidget.h
#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include "user.h"

class AvatarWidget : public QLabel
{
    Q_OBJECT

public:
    AvatarWidget(User* user, QWidget* parent = nullptr);
    QSize sizeHint() const override;

    void setUser(User* user);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void updateAvatar(const QString& path);
    User* m_user;
};

#endif // AVATARWIDGET_H

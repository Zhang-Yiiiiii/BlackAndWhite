// avatarwidget.cpp
#include "avatarwidget.h"
#include "userutils.h"
#include <QFileDialog>
#include <QDir>
#include <QSize>

const QSize avatar_size = QSize(120, 120);

AvatarWidget::AvatarWidget(User* user, QWidget* parent)
    : QLabel(parent), m_user(user)
{
    setCursor(Qt::PointingHandCursor);
    setFixedSize(avatar_size);
    setScaledContents(true);

    if(!user)
    {
        updateAvatar("");
    }
    else
    {
        updateAvatar(m_user->getAvatarPath());

    }

    //setStyleSheet("border-radius: 50px; border: 2px solid black;");
    //setMask(QRegion(0, 0, 100, 100, QRegion::Ellipse)); // 关键：裁剪点击区域
}

QSize AvatarWidget::sizeHint() const
{
    return QSize(avatar_size);
}

void AvatarWidget::setUser(User *user)
{
    m_user = user;

    if(!user)
    {
        updateAvatar("");
    }
    else
    {
        updateAvatar(user->getAvatarPath());
    }

}

void AvatarWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        QString filePath = QFileDialog::getOpenFileName(
                               this,
                               tr("选择头像"),
                               QDir::homePath(),
                               tr("Images (*.png *.jpg *.jpeg *.bmp)")
                           );

        if (!filePath.isEmpty())
        {
            QString saveDir = QDir::currentPath() + "/avatars";
            QDir().mkpath(saveDir);
            QString newFilePath = saveDir + "/" + m_user->getUserName() + ".png";

            qDebug() << newFilePath;

            QPixmap(filePath).scaled(avatar_size, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            .save(newFilePath);

            m_user->setAvatarPath(newFilePath);
            updateAvatar(newFilePath);
            // 调用保存函数
            UserUtils::saveSingleUser(m_user);
        }
    }
}

void AvatarWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    // QPainter painter(this);
    // painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    // painter.setBrush(Qt::NoBrush); // 填充颜色
    // painter.setPen(Qt::black);  // 无边框
    // painter.drawEllipse(rect()); // 绘制圆形

}

void AvatarWidget::updateAvatar(const QString& path)
{
    QPixmap avatarPixmap(path);

    if (avatarPixmap.isNull())
    {
        avatarPixmap.load(":/image/default_avatar.png");
    }

    setPixmap(avatarPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

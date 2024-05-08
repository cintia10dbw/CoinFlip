#include "mypushbutton.h"
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>

// MyPushbutton::MyPushbutton(QWidget *parent)
//     : QPushButton{parent}
// {}

MyPushbutton::MyPushbutton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;

    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushbutton::zoom1()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushbutton::zoom2()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(100);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::InBounce);
    animation->start();
}

void MyPushbutton::mousePressEvent(QMouseEvent* e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(pressImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushbutton::mouseReleaseEvent(QMouseEvent* e)
{
    if(this->normalImgPath!="")
    {
        QPixmap pix;
        bool ret=pix.load(normalImgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

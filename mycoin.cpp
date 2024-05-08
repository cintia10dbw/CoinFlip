#include "mycoin.h"
#include <QPixmap>
#include <QString>
#include <QDebug>

// MyCoin::MyCoin(QWidget *parent)
//     : QWidget{parent}
// {}

MyCoin::MyCoin(QString CoinImg)
{
    this->coinImgPath=CoinImg;

    QPixmap pix;
    bool ret=pix.load(coinImgPath);
    if(!ret)
    {
        qDebug() << "图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    this->timer1 = new QTimer;
    this->timer2 = new QTimer;

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/image/Coin000%1.png").arg(this->min++);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min > this->max)
        {
            this->min = 1;
            timer1->stop();
            this->isAnimation=false;
        }
    });

    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/image/Coin000%1.png").arg(this->max--);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug() << "图片加载失败";
            return;
        }

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max < this->min)
        {
            this->max = 8;
            timer2->stop();
            this->isAnimation=false;
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent* e)
{
    if(this->isAnimation||this->iswin)
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

void MyCoin::changeflag()
{
    if(this->flag)
    {
        this->timer1->start(30);
        this->flag = 0;
        this->isAnimation=true;
    }
    else
    {
        this->timer2->start(30);
        this->flag = 1;
        this->isAnimation=true;
    }
}

#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include <QSoundEffect>
#include "mypushbutton.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(320,588);

    setWindowIcon(QIcon(":/image/Coin0001.png"));

    setWindowTitle("选择关卡");

    QMenuBar* bar=menuBar();
    setMenuBar(bar);

    QMenu* start=bar->addMenu("开始");

    QAction* quit=start->addAction("退出");

    connect(quit,&QAction::triggered,[=](){
        this->close();
    });

    QSoundEffect* choosesound = new QSoundEffect;
    choosesound->setSource(QUrl::fromLocalFile(":/image/TapButtonSound.wav"));
    QSoundEffect* backsound = new QSoundEffect;
    backsound->setSource(QUrl::fromLocalFile(":/image/BackButtonSound.wav"));

    MyPushbutton* backbtn = new MyPushbutton(":/image/BackButton.png",":/image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&QPushButton::clicked,[=](){
        qDebug() << "退出";
        backsound->play();
        emit this->chooseback();
    });

    for(int i = 0;i < 20;i++)
    {
        MyPushbutton * menubtn = new MyPushbutton(":/image/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+i%4*70,130+i/4*70);

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(menubtn,&QPushButton::clicked,[=](){
            QString str = QString("选择第%1关").arg(i+1);
            qDebug() << str;
            this->hide();
            play = new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();
            choosesound->play();
            connect(play,&PlayScene::chooseback,[=](){
                this->setGeometry(play->geometry());
                play->hide();
                this->show();
                delete play;
                play = NULL;
            });
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

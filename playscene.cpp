#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QSoundEffect>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include "mycoin.h"
#include "dataconfig.h"

// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}

PlayScene::PlayScene(int levelnum)
{
    this->Index = levelnum;

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

    QSoundEffect* backsound = new QSoundEffect;
    backsound->setSource(QUrl::fromLocalFile(":/image/BackButtonSound.wav"));
    QSoundEffect* flipsound = new QSoundEffect;
    flipsound->setSource(QUrl::fromLocalFile(":/image/ConFlipSound.wav"));
    QSoundEffect* winsound = new QSoundEffect;
    winsound->setSource(QUrl::fromLocalFile(":/image/LevelWinSound.wav"));

    MyPushbutton* backbtn = new MyPushbutton(":/image/BackButton.png",":/image/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&QPushButton::clicked,[=](){
        qDebug() << "退出";
        backsound->play();
        emit this->chooseback();
    });

    QLabel* level = new QLabel;
    level->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str = QString("Level:%1").arg(this->Index);
    level->setFont(font);
    level->setText(str);
    level->setGeometry(30,this->height()-50,120,50);

    QLabel* winlabel = new QLabel;
    winlabel->setParent(this);
    QPixmap winpix;
    winpix.load(":/image/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,winpix.width(),winpix.height());
    winlabel->setPixmap(winpix);
    winlabel->move((this->width()-winpix.width())*0.5,-(winpix.height()));

    dataConfig config;
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            this->gameArray[i][j]=config.mData[this->Index][i][j];
        }
    }

    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            QLabel* label = new QLabel;
            label->setParent(this);
            QPixmap pix;
            pix.load(":/image/BoardNode.png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(57+i*50,200+j*50);

            QString coinImg;
            if(gameArray[i][j]==1)
            {
                coinImg=":/image/Coin0001.png";
            }
            if(gameArray[i][j]==0)
            {
                coinImg=":/image/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(coinImg);
            coin->setParent(this);
            coin->move(59+i*50,202+j*50);

            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];

            coinbtn[i][j]=coin;

            connect(coin,&QPushButton::clicked,[=](){
                coin->changeflag();
                flipsound->play();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinbtn[coin->posX+1][coin->posY]->changeflag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinbtn[coin->posX-1][coin->posY]->changeflag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinbtn[coin->posX][coin->posY+1]->changeflag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinbtn[coin->posX][coin->posY-1]->changeflag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                    }

                    coin->iswin = true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag == false)
                            {
                                coin->iswin = false;
                                break;
                            }
                        }
                    }
                    if(coin->iswin == true)
                    {
                        qDebug() << "shengli";
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinbtn[i][j]->iswin=true;
                            }
                        }

                        winsound->play();

                        QPropertyAnimation* animation = new QPropertyAnimation(winlabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y()+120,winlabel->width(),winlabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

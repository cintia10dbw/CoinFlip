#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"
#include <QSoundEffect>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(320,588);

    setWindowIcon(QIcon(":/image/Coin0001.png"));

    setWindowTitle("翻金币");

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    MyPushbutton* startbtn = new MyPushbutton(":/image/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    choose = new ChooseLevelScene;

    connect(choose,&ChooseLevelScene::chooseback,[=](){
        this->setGeometry(choose->geometry());
        choose->hide();
        this->show();
    });

    QSoundEffect* startsound = new QSoundEffect;
    startsound->setSource(QUrl::fromLocalFile(":/image/TapButtonSound.wav"));

    connect(startbtn,&MyPushbutton::clicked,[=](){
        qDebug() << "点击";
        startbtn->zoom1();
        startbtn->zoom2();
        startsound->play();
        QTimer::singleShot(200,this,[=](){
            choose->setGeometry(this->geometry());
            this->hide();
            choose->show();
        });
    });
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/image/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

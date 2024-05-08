#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString CoinImg);

    QString coinImgPath;

    int posX;
    int posY;
    bool flag;

    void changeflag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;

    bool isAnimation = false;

    bool iswin = false;

    void mousePressEvent(QMouseEvent* e);

signals:
};

#endif // MYCOIN_H

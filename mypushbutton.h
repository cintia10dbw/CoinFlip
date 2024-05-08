#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushbutton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushbutton(QWidget *parent = nullptr);
    MyPushbutton(QString normalImg,QString pressImg="");

    QString normalImgPath;
    QString pressImgPath;

    void zoom1();
    void zoom2();

    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
};

#endif // MYPUSHBUTTON_H

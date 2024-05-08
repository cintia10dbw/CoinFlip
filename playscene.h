#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelnum);

    int Index;

    int gameArray[4][4];

    MyCoin* coinbtn[4][4];

    void paintEvent(QPaintEvent*);

signals:
    void chooseback();
};

#endif // PLAYSCENE_H

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "boxgroup.h"
#include <QDebug>


class GameView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent=0);

public slots:
    void startGame();
    void clearFullRows();
    void moveBox();
    void gameOver();

private:
    BoxGroup* boxGroup;
    BoxGroup* nextBoxGroup;

    QGraphicsLineItem *topLine;
    QGraphicsLineItem *bottomLine;
    QGraphicsLineItem *leftLine;
    QGraphicsLineItem *rightLine;

    qreal gameSpeed;
    QList<int> rows;

    void initView();
    void initGame();
    void updateScore(const int fullRowNum=0);
};

#endif // GAMEVIEW_H

/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef COINCOUNTER_H
#define COINCOUNTER_H

#include <QGraphicsTextItem>

class CoinCounter: public QGraphicsTextItem{
public:
    CoinCounter(QGraphicsItem * parent=0);
    void increase();
    int getCount();
private:
    int coinCount;
};

#endif // COINCOUNTER_H

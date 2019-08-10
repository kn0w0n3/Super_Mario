/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef TIMER_H
#define TIMER_H

#include <QGraphicsTextItem>

class Timer: public QGraphicsTextItem{
public:
    Timer(QGraphicsItem * parent=0);
    void decrease();
    int getTime();
    void timerEvent(QTimerEvent *);

private:
    int timeCount;
};
#endif // TIMER_H

/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    void increase();
    int getScore();


private:
    int scoreCount;
};
#endif // SCORE_H

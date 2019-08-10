/*
 * Author: equati0n
 * Date: December 2016
*/

#include "score.h"
#include <QFont>
#include<QFontDatabase>


Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the coinCount to 0
    scoreCount = 0;

    // draw the text
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(scoreCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2",30));


}

void Score::increase(){
    scoreCount++;
    setPlainText(QString("") + QString::number(scoreCount * 15));

}

int Score::getScore(){
    return scoreCount;
}


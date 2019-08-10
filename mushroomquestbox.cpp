/*
 * Author: equati0n
 * Date: December 2016
*/

#include "mushroomquestbox.h"
#include <QPainter>


MushroomQuestBox::MushroomQuestBox(int length,QGraphicsItem *parent) : QGraphicsItem(parent) ,mCurrentFrame(), mLength(length) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/questbox.png");
}

void MushroomQuestBox::nextFrame(){

    mCurrentFrame += 50;
    if (mCurrentFrame >= 800 ){
        mCurrentFrame = 0;    
    }
}

QRectF MushroomQuestBox::boundingRect() const{

    return QRectF(0,0,48* mLength,48);
}

void MushroomQuestBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 48*mLength; ++i){
        painter->drawPixmap(i*48,0, mPixmap, mCurrentFrame, 0,48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}

int MushroomQuestBox::type() const{

  return Type;
}

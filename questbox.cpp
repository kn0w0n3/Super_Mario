/*
 * Author: equati0n
 * Date: December 2016
*/

#include "questbox.h"
#include <QPainter>


QuestBox::QuestBox(int length,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame4(), mLength(length)

{
    setFlag(ItemClipsToShape);
    mPixmap4 = QPixmap(":images/questbox.png");

}

void QuestBox::nextFrame4(){

    mCurrentFrame4 += 50;
    if (mCurrentFrame4 >= 800 ) {
        mCurrentFrame4 = 0;
        //mPos.setX( mPos.x() + 5);
    }
}

QRectF QuestBox::boundingRect() const {
    return QRectF(0,0,48* mLength,48);

}

void QuestBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 48*mLength; ++i) {
        painter->drawPixmap(i*48,0, mPixmap4, mCurrentFrame4, 0,48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}


int QuestBox::type() const
{
  return Type;
}

/*
 * Author: equati0n
 * Date: December 2016
*/

#include "notebox.h"
#include <QPainter>

NoteBox::NoteBox(int length,QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame(), mLength(length)

{
    setFlag(ItemClipsToShape);
    mPixmap10 = QPixmap(":images/notebox.png");

}

void NoteBox::nextFrame(){

    mCurrentFrame += 65;
    if (mCurrentFrame >= 518 ) {
        mCurrentFrame = 0;

    }
}

QRectF NoteBox::boundingRect() const {
    return QRectF(0,0,63* mLength,63);

}

void NoteBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 63*mLength; ++i) {
        painter->drawPixmap(i*63,0, mPixmap10, mCurrentFrame, 0,63, 63);
    }
    setTransformOriginPoint(boundingRect().center());
}

int NoteBox::type() const {

  return Type;
}

/*
 * Author: equati0n
 * Date: December 2016
*/

#include "backgrounditem.h"

BackgroundItem::BackgroundItem(const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
}

QPainterPath BackgroundItem::shape() const
{
    return QPainterPath();
}

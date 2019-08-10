/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};

#endif // BACKGROUNDITEM_H

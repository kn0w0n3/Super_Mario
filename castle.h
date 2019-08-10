/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef CASTLE_H
#define CASTLE_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "objecttype.h"


class Castle : public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT

public:
     explicit Castle(QGraphicsItem *parent = 0);
     enum { Type = UserType + castleType };
     int type() const;

private:

};



#endif // CASTLE_H

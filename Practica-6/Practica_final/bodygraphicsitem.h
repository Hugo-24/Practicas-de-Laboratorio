#ifndef BODYGRAPHICSITEM_H
#define BODYGRAPHICSITEM_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include "body.h"

class BodyGraphicsItem : public QGraphicsEllipseItem
{
public:
    BodyGraphicsItem(Body *body, QGraphicsItem *parent = nullptr);

    void updatePosition();
    Body* body() const;

private:
    Body *m_body;
};

#endif // BODYGRAPHICSITEM_H

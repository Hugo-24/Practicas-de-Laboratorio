#include "bodygraphicsitem.h"
#include <QPen>
#include <QBrush>

BodyGraphicsItem::BodyGraphicsItem(Body *body, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_body(body)
{
    // Escalamos el radio para visualización (los valores reales son muy grandes)
    double scaledRadius = body->radius() / 50.0; // Cambiado de 100.0 a 50.0 para hacerlos más grandes
    setRect(-scaledRadius, -scaledRadius, scaledRadius*2, scaledRadius*2);

    // Color y estilo
    setBrush(QBrush(Qt::blue));
    setPen(QPen(Qt::black));
}

void BodyGraphicsItem::updatePosition()
{
    // Escalamos las coordenadas para visualización
    double scale = 1.0 / 50.0; // Mismo factor de escala que el radio
    setPos(m_body->x() * scale, m_body->y() * scale);
}

Body* BodyGraphicsItem::body() const
{
    return m_body;
}

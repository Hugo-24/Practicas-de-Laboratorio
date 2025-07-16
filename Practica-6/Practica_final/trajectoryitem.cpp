#include "trajectoryitem.h"
#include <QPen>

TrajectoryItem::TrajectoryItem(QColor color, QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    setPen(QPen(color, 1));
    setBrush(Qt::NoBrush);
}

void TrajectoryItem::addPoint(QPointF point)
{
    if (m_path.elementCount() == 0) {
        m_path.moveTo(point);
    } else {
        m_path.lineTo(point);
    }
    setPath(m_path);
}

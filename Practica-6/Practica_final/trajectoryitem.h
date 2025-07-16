#ifndef TRAJECTORYITEM_H
#define TRAJECTORYITEM_H

#include <QGraphicsPathItem>

class TrajectoryItem : public QGraphicsPathItem
{
public:
    TrajectoryItem(QColor color, QGraphicsItem *parent = nullptr);
    void addPoint(QPointF point);

private:
    QPainterPath m_path;
};

#endif // TRAJECTORYITEM_H

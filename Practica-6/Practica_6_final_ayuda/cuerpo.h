#ifndef CUERPO_H
#define CUERPO_H

#include <cmath>
#include <math.h>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>

#include <QVector>
#include <QPointF>

class cuerpo: public QObject, public QGraphicsItem {

    Q_OBJECT

private:
    double posX, posY;
    double velX, velY;
    double aceX, aceY;
    double masa;
    double radio;

    QColor color;

    double dt = 0.016;

    QVector<QPointF> trayectoria;

public:

    cuerpo(double x, double y, double vx, double vy, double m, double r, QColor c);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void actualizarPosicion(int w, int h);

    void calcularAceleracion(QList <cuerpo*> cuerpos);


    double getX();
    double getY();
    double getM();

};

#endif // CUERPO_H

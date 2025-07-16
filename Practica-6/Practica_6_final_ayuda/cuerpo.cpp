#include "cuerpo.h"
#include <QPainter>
#include <cmath>

const double G = 1; //const double G = 6.67430e-11;
const int VS = 10000; //velocidad de la simulación
const double escala = 0.05;

cuerpo::cuerpo(double x, double y, double vx, double vy, double m, double r, QColor c)
    : posX(x), posY(y), velX(vx), velY(vy), masa(m), radio(r), color(c) {}

void cuerpo::calcularAceleracion(QList <cuerpo*> cuerpos){

    aceX = 0;
    aceY = 0;

    for (cuerpo* c : cuerpos){
        if (c != this){
            double dx = c->getX() - posX;
            double dy = c->getY() - posY;
            double dis = sqrt(dx * dx + dy * dy);

            if (dis > 0.01) {
                double fuerza = (G * c->getM()) / (dis * dis);
                aceX += fuerza * (dx / dis);  // usar componente X del vector unitario
                aceY += fuerza * (dy / dis);  // usar componente Y del vector unitario
            }
        }
    }
}

int normalX(float x, int w){
    return static_cast<int>(((1 - (x / -6000.0)) * w) / 2);
}

int normalY(float y, int h){
    return static_cast<int>(((1 - (y / 6000.0)) * h) / 2);
}

void cuerpo:: actualizarPosicion(int w, int h) {

    velX += aceX * dt * VS;
    velY += -aceY * dt * VS;

    posX += velX * dt + 0.5 * aceX * dt * dt;
    posY += velY * dt + 0.5 * (-aceY) * dt * dt;

    trayectoria.append(QPointF(x(), y()));

    //setX(normalX(posX,w));
    //setY(normalY(posY,h));

    setPos(posX, -posY); //invertimos Y para ey "arriba sea arriba"

}

double cuerpo:: getX() { return posX; }
double cuerpo:: getY() { return posY; }
double cuerpo:: getM() { return masa; }


//QRectF cuerpo::boundingRect() const {

  //  return QRectF(-1*escala*radio, -1*escala*radio, 2*escala*radio, 2*escala*radio);
//}

QRectF cuerpo::boundingRect() const {
    return QRectF(-radio/2, -radio/2, radio, radio);
}

void cuerpo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setBrush(color);
    painter->drawEllipse(boundingRect());

    // Dibujar trayectoria
    painter->setPen(QPen(Qt::black, 1));
    for (int i = 1; i < trayectoria.size(); ++i) {
        painter->drawLine(trayectoria[i - 1] - pos(), trayectoria[i] - pos());
    }
}

#include "body.h"
#include <cmath>

Body::Body(QObject *parent) : QObject(parent),
    m_x(0), m_y(0), m_mass(0), m_radius(0),
    m_velocityX(0), m_velocityY(0) {}

Body::Body(double x, double y, double mass, double radius,
           double vx, double vy, QObject *parent) :
    QObject(parent), m_x(x), m_y(y), m_mass(mass),
    m_radius(radius), m_velocityX(vx), m_velocityY(vy) {}

// Getters
double Body::x() const { return m_x; }
double Body::y() const { return m_y; }
double Body::mass() const { return m_mass; }
double Body::radius() const { return m_radius; }
double Body::velocityX() const { return m_velocityX; }
double Body::velocityY() const { return m_velocityY; }

// Setters
void Body::setPosition(double x, double y) {
    m_x = x;
    m_y = y;
}

void Body::setVelocity(double vx, double vy) {
    m_velocityX = vx;
    m_velocityY = vy;
}

void Body::updatePosition(double dt) {
    m_x += m_velocityX * dt;
    m_y += m_velocityY * dt;
}

void Body::calculateAcceleration(const Body &other, double &ax, double &ay) const {
    const double G = 1; //6.67384e-11; // Constante gravitacional

    double dx = other.x() - m_x;
    double dy = other.y() - m_y;
    double r = sqrt(dx*dx + dy*dy);

    if (r == 0) return; // Evitar división por cero

    double force = (G * other.mass()) / (r*r);
    double theta = atan2(dy, dx);

    ax = force * cos(theta);
    ay = force * sin(theta);
}

void Body::applyAcceleration(double ax, double ay, double dt) {
    m_velocityX += ax * dt;
    m_velocityY += ay * dt;
}

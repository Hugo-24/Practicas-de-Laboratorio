#ifndef BODY_H
#define BODY_H

#include <QObject>
#include <QPointF>

class Body : public QObject
{
    Q_OBJECT
public:
    explicit Body(QObject *parent = nullptr);
    Body(double x, double y, double mass, double radius,
         double vx, double vy, QObject *parent = nullptr);

    // Getters
    double x() const;
    double y() const;
    double mass() const;
    double radius() const;
    double velocityX() const;
    double velocityY() const;

    // Setters
    void setPosition(double x, double y);
    void setVelocity(double vx, double vy);

    // Actualiza la posición basada en la velocidad y aceleración
    void updatePosition(double dt);
    // Calcula la aceleración causada por otro cuerpo
    void calculateAcceleration(const Body &other, double &ax, double &ay) const;
    // Añade aceleración a la velocidad
    void applyAcceleration(double ax, double ay, double dt);

private:
    double m_x, m_y;         // Posición
    double m_mass;           // Masa
    double m_radius;         // Radio (para visualización)
    double m_velocityX;      // Velocidad en X
    double m_velocityY;      // Velocidad en Y
};

#endif // BODY_H

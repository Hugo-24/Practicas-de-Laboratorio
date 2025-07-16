#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsEllipseItem>
#include <QVector2D>

// Esta clase representa un cuerpo con masa, posición y velocidad
// que se puede visualizar y simular dentro de una escena gráfica.
class Cuerpo : public QGraphicsEllipseItem
{
public:
    // Constructor del cuerpo
    Cuerpo(float masa, float radio, float posX, float posY,
           float velX = 0.0f, float velY = 0.0f);

    // Actualiza su estado físico (física real)
    void actualizarPosicion(float dt);
    void actualizarVelocidad(const QVector2D& aceleracion, float dt);

    // Calcula aceleración gravitacional que otro cuerpo produce sobre este
    QVector2D calcularAceleracion(const Cuerpo& otro) const;

    void establecerAceleracion(const QVector2D& nuevaAceleracion); //Aceleracion del cuerpo

    // Getters para estado físico
    float obtenerMasa() const;
    QVector2D obtenerPosicion() const;
    QVector2D obtenerVelocidad() const;

    // Setter de velocidad manual
    void establecerVelocidad(const QVector2D& nuevaVelocidad);

    // Opcional: actualizar posición visual según estado físico
    void actualizarGrafico(double escala);

private:
    float masa;           // Masa del cuerpo
    float radio;          // Radio real del cuerpo (físico)
    QVector2D posicion;   // Posición física (no visual)
    QVector2D velocidad;  // Velocidad física
    QVector2D aceleracionActual;  // Se actualiza en cada paso
};

#endif // CUERPO_H

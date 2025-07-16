#include "cuerpo.h"
#include <QtMath>
#include <QBrush>

const float G = 1.0f;  // Constante gravitacional simplificada

// Constructor que inicializa atributos físicos y configura la apariencia
Cuerpo::Cuerpo(float masa, float radio, float posX, float posY,
               float velX, float velY)
    : masa(masa),
    radio(radio),
    posicion(posX, posY),
    velocidad(velX, velY)
{
    // El tamaño visual se establecerá desde fuera (usando escala)
    setBrush(QBrush(Qt::blue)); // Color por defecto
}

// Actualiza la posición física y sincroniza visualmente
void Cuerpo::actualizarPosicion(float dt)
{
    // MRUV completo: x = x0 + v·t + 0.5·a·t²
    posicion += velocidad * dt + 0.5 * aceleracionActual * dt * dt;
    // La posición gráfica se puede actualizar desde fuera con escala
}

// Actualiza la velocidad en base a una aceleración externa
void Cuerpo::actualizarVelocidad(const QVector2D& aceleracion, float dt)
{
    // v = v0 + a * dt
    velocidad += aceleracion * dt;
}

// Calcula la aceleración que otro cuerpo ejerce sobre este
QVector2D Cuerpo::calcularAceleracion(const Cuerpo& otro) const
{
    QVector2D direccion = otro.posicion - posicion;
    float distancia = direccion.length();

    // Evitar división por cero o colapsos numéricos
    if (distancia < 1.0f)
        distancia = 1.0f;

    direccion.normalize(); // Vector unitario

    // Fórmula: a = G * m / r²
    float magnitud = G * otro.masa / (distancia * distancia);

    return direccion * magnitud;
}

void Cuerpo::establecerAceleracion(const QVector2D& nuevaAceleracion)
{
    aceleracionActual = nuevaAceleracion;
}

// Getter para masa
float Cuerpo::obtenerMasa() const
{
    return masa;
}

// Getter para posición física
QVector2D Cuerpo::obtenerPosicion() const
{
    return posicion;
}

// Getter para velocidad
QVector2D Cuerpo::obtenerVelocidad() const
{
    return velocidad;
}

// Setter de velocidad manual
void Cuerpo::establecerVelocidad(const QVector2D& nuevaVelocidad)
{
    velocidad = nuevaVelocidad;
}

// Actualiza la posición visual (gráfica) del cuerpo según su posición física y escala
void Cuerpo::actualizarGrafico(double escala)
{
    // Mueve el cuerpo al lugar correcto en la escena
    setPos(posicion.x() * escala, posicion.y() * escala);
}

#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPoint>

/**
 * Clase base para cualquier entidad con posición lógica en el laberinto.
 * Incluye posición en filas/columnas y manejo de posición gráfica.
 */
class Entidad : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    // Constructor.
    Entidad(int fila, int columna, int tamCelda, QObject* parent = nullptr);

    // Accesores
    int getFila() const;
    int getColumna() const;
    int getTamCelda() const;

    // Modificadores
    void setFila(int f);
    void setColumna(int c);
    void setPosicion(int fila, int columna);

protected:
    int fila;       // Posición lógica en el mapa
    int columna;
    int tamCelda;   // Tamaño de celda en píxeles (usado para dibujar)
};

#endif // ENTIDAD_H

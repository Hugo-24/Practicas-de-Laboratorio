#ifndef GALLETA_H
#define GALLETA_H

#include <QGraphicsPixmapItem>
#include <QString>

/**
 * Clase que representa una galleta comestible por Pacman.
 * Puede ser normal o especial (fruta, cereza, etc).
 */
class Galleta : public QGraphicsPixmapItem {
public:
    Galleta(int fila, int columna, int tamCelda, bool especial = false);

    // Tipo de galleta
    bool esEspecial() const;

private:
    bool especial; // true si es comida especial tipo fruta
};

#endif // GALLETA_H

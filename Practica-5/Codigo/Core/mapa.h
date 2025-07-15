#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <string>
#include <QString>

class QGraphicsScene;

/**
 * Clase que representa el mapa de Pac-Man leído desde un archivo de texto.
 */
class Mapa {
public:
    Mapa();

    bool cargarDesdeRecurso(const QString& ruta);
    const std::vector<std::string>& obtenerMapa() const;

    // Devuelve el carácter de una celda
    char getCelda(int fila, int columna) const;

    // Verifica si una celda se puede caminar
    bool esCeldaLibre(int fila, int columna) const;

    int filas() const;
    int columnas() const;

    // Dibuja las paredes (celdas '1') en la escena
    void dibujar(QGraphicsScene* escena, int tamCelda) const;

private:
    std::vector<std::string> matriz;
};

#endif // MAPA_H

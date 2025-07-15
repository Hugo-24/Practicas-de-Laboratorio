#include "entidad.h"

Entidad::Entidad(int fila, int columna, int tamCelda, QObject* parent)
    : QObject(parent), fila(fila), columna(columna), tamCelda(tamCelda) {
    setZValue(2); // Asegura que se dibuje sobre fondo/objetos
    setPos(columna * tamCelda, fila * tamCelda); // Posición gráfica
}

int Entidad::getFila() const {
    return fila;
}

int Entidad::getColumna() const {
    return columna;
}

int Entidad::getTamCelda() const {
    return tamCelda;
}

void Entidad::setFila(int f) {
    fila = f;
    setPos(columna * tamCelda, fila * tamCelda); // Actualiza posición visual
}

void Entidad::setColumna(int c) {
    columna = c;
    setPos(columna * tamCelda, fila * tamCelda);
}

void Entidad::setPosicion(int f, int c) {
    fila = f;
    columna = c;
    setPos(columna * tamCelda, fila * tamCelda);
}

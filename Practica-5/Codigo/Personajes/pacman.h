#ifndef PACMAN_H
#define PACMAN_H

#include "Codigo/Core/entidad.h"
#include <QTimer>
#include <QKeyEvent>
#include <vector>
#include <string>

class Juego;

/**
 * Clase que representa a Pacman.
 * Se mueve de forma continua en píxeles, pero verifica colisiones por celdas.
 */
class Pacman : public Entidad {
    Q_OBJECT

public:
    Pacman(const std::vector<std::string>& laberinto, Juego* juego);

    void keyPressEvent(QKeyEvent* event) override; // Captura teclas
    void reiniciar();                              // Reinicia posición

    int getFila() const { return fila; }
    int getColumna() const { return columna; }
    void detenerMovimiento();
    void reanudarMovimiento();
    void iniciarAnimacion();  // Activa la animación boca abierta/cerrada

private:
    void mover();             // Mueve a Pacman en cada tick
    void alternarSprite();    // Cambia entre sprite abierto/cerrado
    const std::vector<std::string>& lab;  // Mapa lógico
    Juego* controlador;                   // Referencia al juego

    int dirFila;        // Dirección actual
    int dirColumna;
    int sigFila;        // Dirección deseada por el jugador
    int sigColumna;

    bool bocaAbierta;   // Estado de la animación
    QTimer* movimientoTimer;
    QTimer* animacionTimer;

    QPixmap spriteIdle;  // Nuevo sprite para el estado inicial
    QPixmap spriteAbierto;
    QPixmap spriteCerrado;

    int filaInicial;
    int colInicial;

    int velocidadPx = 1; // Píxeles por frame (recomendado: 2 para 60 fps)

    bool puedeMover(int f, int c) const;  // Verifica si puede ir a una celda
    bool hayMuroAdelante() const;         // Revisa si colisionaría con pared
};

#endif // PACMAN_H

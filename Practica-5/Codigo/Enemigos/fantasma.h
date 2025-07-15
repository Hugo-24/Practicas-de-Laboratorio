#ifndef FANTASMA_H
#define FANTASMA_H

#include "../Core/entidad.h"
#include <vector>
#include <string>
#include <QTimer>

class Juego;

/**
 * Clase que representa un fantasma enemigo en Pac-Man.
 * Se mueve continuamente en una dirección aleatoria válida.
 * Puede volverse vulnerable si Pacman come una galleta especial.
 * Revive tras ser comido y respawnea en su posición inicial.
 */
class Fantasma : public Entidad {
    Q_OBJECT

public:
    Fantasma(const std::vector<std::string>& laberinto, Juego* juego, int filaInicio, int colInicio);

    void activarModoComestible();     // Cambia sprite y estado a vulnerable
    void restaurarSpriteNormal();     // Vuelve al sprite normal
    void reiniciar();                 // Reinicia la posición y estado
    bool estaVulnerable() const;      // Getter de estado vulnerable
    void iniciarRespawn();  // Inicia el temporizador de respawn
    int getFilaInicial() const { return filaInicial; }
    int getColumnaInicial() const { return columnaInicial; }
    void detenerMovimiento();     // Detiene el timer
    void mostrarInvisible();      // Lo oculta

private:
    void mover();                     // Movimiento automático
    void revivir();                   // Reaparición tras ser comido
    const std::vector<std::string>& lab; // Referencia al mapa lógico
    Juego* controlador;                 // Referencia al juego

    int dirFila, dirColumna;           // Dirección actual
    int filaInicial, columnaInicial;   // Posición de respawn

    QTimer* movimientoTimer;           // Controla la animación continua
    QTimer* respawnTimer;              // Controla el tiempo muerto tras ser comido

    QPixmap spriteNormal;              // Imagen normal
    QPixmap spriteComestible;          // Imagen vulnerable

    bool vulnerable = false;           // Si puede ser comido por Pacman
    bool enRespawn = false;            // Si está esperando reaparecer

    int velocidadPx = 2;               // Velocidad (pixeles por frame)

    // Auxiliares
    bool puedeMoverA(int f, int c) const;
    void elegirNuevaDireccion();
    bool hayMuroAdelante() const;
};

#endif // FANTASMA_H

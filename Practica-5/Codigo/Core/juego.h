#ifndef JUEGO_H
#define JUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <vector>
#include <string>
#include "mapa.h"

class Pacman;
class Fantasma;
class Galleta;

/**
 * Clase central del juego Pac-Man.
 * Controla el mapa, personajes, galletas, colisiones y estados del juego.
 */
class Juego : public QObject {
    Q_OBJECT

public:
    explicit Juego(QGraphicsView* vista, QObject* parent = nullptr);

    // Gestión de juego
    void perderVida();
    void actualizarPuntaje(int puntosExtra);
    void actualizarPosicionJugador(int fila, int columna);

    // Estados
    bool estaInvulnerable() const;
    int getFilaJugador() const;
    int getColumnaJugador() const;
    const std::vector<std::string>& obtenerMapa() const;

    // Colisiones
    void verificarColisionGalletas(Pacman* pacman);
    void verificarColisionFantasma(Pacman* pacman);

    // Modo especial
    void activarModoComerFantasmas();
    void finModoEspecial();

private:
    void finInvulnerabilidad() ;
    // Vista y escena principal
    QGraphicsView* vista;
    QGraphicsScene* escena;

    // Entidades del juego
    Mapa mapa;
    Pacman* pacman;
    std::vector<Fantasma*> fantasmas;
    std::vector<Galleta*> galletas;

    // Estado del juego
    int vidas = 3;
    int puntaje = 0;
    int filaJugador = 1;
    int columnaJugador = 1;
    int galletasTotales = 0;
    int galletasComidas = 0;
    bool invulnerable = false;
    bool juegoTerminado = false;

    // Texto HUD
    QGraphicsTextItem* textoVidas = nullptr;
    QGraphicsTextItem* textoPuntaje = nullptr;

    // Timers
    QTimer* invulnerableTimer;
    QTimer* modoEspecialTimer;

    // Métodos auxiliares
    void crearHUD();
    void crearPersonajes();
    void cargarGalletas();
    void verificarVictoria();
    void gameOver();
    void victoria();
    void reiniciarNivel(); // Reinicia todo el nivel desde cero
    void detenerSonidos(); // Detiene todos los sonidos activos
    // Interfaz visual
    QLabel* mensajePantalla = nullptr;

    // Audio
    // Sonidos generales
    QMediaPlayer* reproductor;
    QAudioOutput* salidaAudio;

    // Sonido de comer galletas
    QMediaPlayer* sonidoComer;
    QAudioOutput* salidaComer;
    //Sonido fantasmas
    QMediaPlayer* sonidoFantasma = nullptr;
    QMediaPlayer* sonidoPoder = nullptr;
    QAudioOutput* salidaFantasma = nullptr;
    QAudioOutput* salidaPoder = nullptr;

};

#endif // JUEGO_H

#include "fantasma.h"
#include "../Core/juego.h"
#include <QRandomGenerator>
#include <QDebug>
#include <algorithm>

Fantasma::Fantasma(const std::vector<std::string>& laberinto, Juego* juego, int filaInicio, int colInicio)
    : Entidad(filaInicio, colInicio, 8),
    lab(laberinto),
    controlador(juego),
    dirFila(0), dirColumna(1),
    filaInicial(filaInicio), columnaInicial(colInicio),
    movimientoTimer(new QTimer(this)),
    respawnTimer(new QTimer(this)),
    vulnerable(false), enRespawn(false)
{
    spriteNormal.load(":/Sprites/fantasma.png");
    spriteComestible.load(":/Sprites/fantasma2.png");

    if (spriteNormal.isNull() || spriteComestible.isNull())
        qDebug() << "ERROR: no se pudieron cargar los sprites del fantasma";

    setPixmap(spriteNormal.scaled(tamCelda, tamCelda));
    setZValue(1.9);

    // Movimiento fluido cada 50ms
    connect(movimientoTimer, &QTimer::timeout, this, &Fantasma::mover);
    movimientoTimer->start(50);  // ~20 FPS

    // Timer para reaparecer
    respawnTimer->setSingleShot(true);
    connect(respawnTimer, &QTimer::timeout, this, &Fantasma::revivir);
    qDebug() << "Fantasma empieza en fila:" << fila << "columna:" << columna;
    qDebug() << "Valor en esa celda:" << lab[fila][columna];
}

void Fantasma::mover() {
    if (enRespawn) return;

    // Teletransporte por túnel en fila 14
    if (static_cast<int>(y()) % tamCelda == 0) {
        int filaActual = static_cast<int>(y()) / tamCelda;
        int colActual  = static_cast<int>(x()) / tamCelda;

        if (filaActual == 15) {
            if (colActual == 0 && dirColumna == -1) {
                // Va a la izquierda desde el borde
                setPos(28 * tamCelda, y());
                columna = 28;
                return;
            }
            else if (colActual == 28 && dirColumna == 1) {
                // Va a la derecha desde el borde
                setPos(0, y());
                columna = 0;
                return;
            }
        }
    }

    // Movimiento por píxeles
    setPos(x() + dirColumna * velocidadPx, y() + dirFila * velocidadPx);

    // Si aún no está alineado a celda, no hacer nada más
    if ((static_cast<int>(x()) % tamCelda != 0) || (static_cast<int>(y()) % tamCelda != 0))
        return;

    // Actualizar lógica solo cuando está bien alineado
    fila = static_cast<int>(y()) / tamCelda;
    columna = static_cast<int>(x()) / tamCelda;

    // Detectar colisión con Pacman (solo si están alineados)
    if (fila == controlador->getFilaJugador() &&
        columna == controlador->getColumnaJugador()) {
        if (vulnerable) {
            enRespawn = true;
            vulnerable = false;
            movimientoTimer->stop();
            setVisible(false);
            setPos(columnaInicial * tamCelda, filaInicial * tamCelda);
            respawnTimer->start(1000);
            controlador->actualizarPuntaje(200);
        } else if (!controlador->estaInvulnerable()) {
            controlador->perderVida();
        }
    }

    // Cada cierto tiempo cambiar de dirección aleatoriamente
    if (QRandomGenerator::global()->bounded(200) < 20) {
        elegirNuevaDireccion();
    }

    // Si hay muro por delante, forzar dirección nueva
    int f2 = fila + dirFila;
    int c2 = columna + dirColumna;
    if (!puedeMoverA(f2, c2)) {
        elegirNuevaDireccion();
    }
}

bool Fantasma::puedeMoverA(int f, int c) const {
    return f >= 0 && c >= 0 &&
           f < static_cast<int>(lab.size()) &&
           c < static_cast<int>(lab[0].size()) &&
           lab[f][c] != '1';
}

void Fantasma::elegirNuevaDireccion() {
    std::vector<std::pair<int, int>> direcciones = {
        { -1, 0 }, // arriba
        { -1, 0 }, // arriba
        { 0, -1 }, // izquierda
        { 0, 1 },  // derecha
        { 1, 0 }   // abajo
    };

    // Evitar retroceder si se puede
    std::pair<int, int> reversa = {-dirFila, -dirColumna};

    std::shuffle(direcciones.begin(), direcciones.end(), *QRandomGenerator::global());

    for (const auto& [df, dc] : direcciones) {
        if (std::make_pair(df, dc) == reversa) continue;
        if (puedeMoverA(fila + df, columna + dc)) {
            dirFila = df;
            dirColumna = dc;
            return;
        }
    }

    // Si nada sirvió, permitir reversa
    for (const auto& [df, dc] : direcciones) {
        if (puedeMoverA(fila + df, columna + dc)) {
            dirFila = df;
            dirColumna = dc;
            return;
        }
    }

    // Si no puede moverse a ningún lado
    dirFila = 0;
    dirColumna = 0;
}

void Fantasma::activarModoComestible() {
    if (!spriteComestible.isNull() && !enRespawn) {
        setPixmap(spriteComestible.scaled(tamCelda, tamCelda));
        vulnerable = true;
    }
}

void Fantasma::restaurarSpriteNormal() {
    if (!enRespawn) {
        setPixmap(spriteNormal.scaled(tamCelda, tamCelda));
        vulnerable = false;
    }
}

bool Fantasma::estaVulnerable() const {
    return vulnerable;
}

void Fantasma::detenerMovimiento() {
    movimientoTimer->stop();
}

void Fantasma::mostrarInvisible() {
    setVisible(false);
}

void Fantasma::revivir() {
    fila = filaInicial;
    columna = columnaInicial;
    setPos(columna * tamCelda, fila * tamCelda);
    setPixmap(spriteNormal.scaled(tamCelda, tamCelda));
    vulnerable = false;
    enRespawn = false;
    setVisible(true);
    dirFila = 0;
    dirColumna = 1;
    movimientoTimer->start(50);
}

void Fantasma::reiniciar() {
    fila = filaInicial;
    columna = columnaInicial;
    setPos(columna * tamCelda, fila * tamCelda);
    dirFila = 0;
    dirColumna = 1;
    vulnerable = false;
    enRespawn = false;
    setVisible(true);
    setPixmap(spriteNormal.scaled(tamCelda, tamCelda));
    movimientoTimer->start(50);
}

void Fantasma::iniciarRespawn() {
    if (enRespawn) return;

    enRespawn = true;
    vulnerable = false;
    movimientoTimer->stop();
    respawnTimer->start(5000);  // Tiempo de espera antes de reaparecer
}

#include "pacman.h"
#include "../Core/juego.h"
#include <QTransform>
#include <QDebug>
#include <QtMath>  // para qFloor()

Pacman::Pacman(const std::vector<std::string>& laberinto, Juego* juego)
    : Entidad(24, 14, 8),  // posición inicial lógica: fila 24, col 14
    lab(laberinto),
    controlador(juego),
    dirFila(0), dirColumna(0),
    sigFila(0), sigColumna(0),
    bocaAbierta(true),
    movimientoTimer(new QTimer(this)),
    animacionTimer(nullptr),  // ← inicialización segura para evitar crash
    filaInicial(24),
    colInicial(14)
{
    // Cargar sprites
    spriteAbierto.load(":/Sprites/pacman_abierto.png");
    spriteCerrado.load(":/Sprites/pacman_cerrado.png");
    spriteIdle.load(":/Sprites/pacman_idle.png");  // Asegúrate que exista en tu qrc

    if (spriteAbierto.isNull() || spriteCerrado.isNull())
        qDebug() << "ERROR: no se pudieron cargar los sprites de Pacman";

    // Sprite inicial
    setPixmap(spriteAbierto.scaled(tamCelda, tamCelda));
    setZValue(2);

    // Habilita control por teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    // Timer para movimiento continuo (cada 16ms = ~60 FPS)
    movimientoTimer = new QTimer(this);
    connect(movimientoTimer, &QTimer::timeout, this, &Pacman::mover);
    movimientoTimer->start(16);  // más fluido

    setPixmap(spriteIdle.scaled(tamCelda, tamCelda));  // Mostrar sprite idle al inicio

    qDebug() << "Pacman empieza en fila:" << fila << "columna:" << columna;
    qDebug() << "Valor en esa celda:" << lab[fila][columna];
}

void Pacman::keyPressEvent(QKeyEvent* event) {
    // Establece la dirección deseada por el jugador
    switch (event->key()) {
    case Qt::Key_W: sigFila = -1; sigColumna = 0; break;
    case Qt::Key_S: sigFila = 1;  sigColumna = 0; break;
    case Qt::Key_A: sigFila = 0;  sigColumna = -1; break;
    case Qt::Key_D: sigFila = 0;  sigColumna = 1; break;
    default: return;
    }
}

void Pacman::iniciarAnimacion() {
    if (!spriteAbierto.isNull())
        setPixmap(spriteAbierto.scaled(tamCelda, tamCelda));

    // Si el timer ya no es válido (corrupto), lo destruimos y creamos nuevo
    if (animacionTimer && !animacionTimer->parent()) {
        qDebug() << "⚠️ Timer inválido, reconstruyendo animacionTimer";
        delete animacionTimer;
        animacionTimer = nullptr;
    }

    if (!animacionTimer) {
        animacionTimer = new QTimer(this);
        connect(animacionTimer, &QTimer::timeout, this, &Pacman::alternarSprite);
    }

    if (animacionTimer && !animacionTimer->isActive()) {
        animacionTimer->start(100);
    }
}
void Pacman::mover() {
    // Solo intentar cambiar de dirección cuando esté perfectamente alineado
    if (static_cast<int>(x()) % tamCelda == 0 && static_cast<int>(y()) % tamCelda == 0) {
        int filaActual = static_cast<int>(y()) / tamCelda;
        int colActual  = static_cast<int>(x()) / tamCelda;

        int nuevaFila = filaActual + sigFila;
        int nuevaCol  = colActual + sigColumna;

        // Si la dirección deseada es válida, la aplicamos
        if (puedeMover(nuevaFila, nuevaCol)) {
            dirFila = sigFila;
            dirColumna = sigColumna;
        }

        // Verificamos si aún podemos movernos en la dirección actual
        int destinoFila = filaActual + dirFila;
        int destinoCol  = colActual + dirColumna;

        if (!puedeMover(destinoFila, destinoCol)) {
            dirFila = 0;
            dirColumna = 0;
        }
    }

    // Avanzamos solo si hay dirección activa
    if (dirFila != 0 || dirColumna != 0) {
        setPos(x() + dirColumna * velocidadPx, y() + dirFila * velocidadPx);
    }

    // Teletransporte horizontal en fila 14
    // Verificar túnel de teletransporte (solo si está alineado verticalmente)
    if (static_cast<int>(y()) % tamCelda == 0) {
        int filaActual = static_cast<int>(y()) / tamCelda;
        int colActual  = static_cast<int>(x()) / tamCelda;

        if (filaActual == 15) {
            if (colActual == 0 && dirColumna == -1) {
                // Izquierda a derecha
                setPos(28 * tamCelda, filaActual * tamCelda);
                fila = filaActual;
                columna = 28;
                controlador->actualizarPosicionJugador(fila, columna);
                controlador->verificarColisionGalletas(this);
                return;
            } else if (colActual == 28 && dirColumna == 1) {
                // Derecha a izquierda
                setPos(0, filaActual * tamCelda);
                fila = filaActual;
                columna = 0;
                controlador->actualizarPosicionJugador(fila, columna);
                controlador->verificarColisionGalletas(this);
                return;
            }
        }
    }

    // Cuando esté perfectamente alineado, actualizamos posición lógica y verificamos colisiones
    if (static_cast<int>(x()) % tamCelda == 0 && static_cast<int>(y()) % tamCelda == 0) {
        fila = static_cast<int>(y()) / tamCelda;
        columna = static_cast<int>(x()) / tamCelda;

        controlador->actualizarPosicionJugador(fila, columna);
        controlador->verificarColisionGalletas(this);
    }
    // Siempre verificar colisión con fantasmas (aunque no esté alineado)
    controlador->verificarColisionFantasma(this);
}

bool Pacman::puedeMover(int f, int c) const {
    // Verifica si la celda destino es válida y no hay muro
    return f >= 0 && f < static_cast<int>(lab.size()) &&
           c >= 0 && c < static_cast<int>(lab[0].size()) &&
           lab[f][c] != '1';
}

bool Pacman::hayMuroAdelante() const {
    // Calcula posición futura en píxeles
    qreal nextX = x() + dirColumna * velocidadPx;
    qreal nextY = y() + dirFila * velocidadPx;

    // Redondeo seguro hacia abajo para evitar errores al borde de una celda
    int f = qFloor(nextY / tamCelda);
    int c = qFloor(nextX / tamCelda);

    // Verifica si esa celda tiene un muro
    return !puedeMover(f, c);
}

void Pacman::alternarSprite() {
    bocaAbierta = !bocaAbierta;

    QPixmap base = bocaAbierta ? spriteAbierto : spriteCerrado;
    QPixmap rotada = base;

    // Rotar sprite según dirección de movimiento
    if (dirFila == -1)        rotada = base.transformed(QTransform().rotate(-90));
    else if (dirFila == 1)    rotada = base.transformed(QTransform().rotate(90));
    else if (dirColumna == -1)rotada = base.transformed(QTransform().rotate(180));

    setPixmap(rotada.scaled(tamCelda, tamCelda));
}

void Pacman::reiniciar() {
    // Restaurar posición y dirección
    setPosicion(filaInicial, colInicial);
    dirFila = 0;
    dirColumna = 0;
    sigFila = 0;
    sigColumna = 0;
}

void Pacman::detenerMovimiento() {
    if (movimientoTimer && movimientoTimer->isActive()) movimientoTimer->stop();
    if (animacionTimer && animacionTimer->isActive()) animacionTimer->stop();
}

void Pacman::reanudarMovimiento() {
    if (movimientoTimer) movimientoTimer->start(16);
    if (animacionTimer) animacionTimer->start(100);
}

#include "juego.h"
#include "fantasma.h"
#include "pacman.h"
#include "galleta.h"

#include <QTimer>
#include <QFont>
#include <QMessageBox>
#include <QDebug>
#include <algorithm>

Juego::Juego(QGraphicsView* vista, QObject* parent)
    : QObject(parent),
    vista(vista),
    escena(new QGraphicsScene(this)),
    invulnerableTimer(new QTimer(this)),
    modoEspecialTimer(new QTimer(this)),
    reproductor(nullptr),
    salidaAudio(nullptr),
    sonidoComer(nullptr),
    salidaComer(nullptr)
{
    // Configura la vista y la escena
    const int tamCelda = 8;
    const int ancho = tamCelda * 29;
    const int alto = tamCelda * 32 + 32;

    vista->setScene(escena);
    vista->setSceneRect(0, 0, ancho, alto);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Cargar el mapa
    if (!mapa.cargarDesdeRecurso(":/Sprites/laberinto.txt")) {
        qDebug() << "ERROR: no se pudo cargar el mapa";
        return;
    }

    mapa.dibujar(escena, tamCelda);

    // Mostrar mensaje de inicio durante 4.4 segundos
    QLabel* mensajeInicio = new QLabel("¡Preparado!", vista);
    mensajeInicio->setStyleSheet("color: yellow; font-size: 30px; background-color: black; padding: 10px;");
    mensajeInicio->adjustSize();
    mensajeInicio->move((vista->width() - mensajeInicio->width()) / 2,
                        (vista->height() - mensajeInicio->height()) / 2);
    mensajeInicio->show();

    // 🎵 Sonido de inicio del juego
    reproductor = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);
    reproductor->setAudioOutput(salidaAudio);
    reproductor->setSource(QUrl("qrc:/Sonidos/inicio.mp3"));
    salidaAudio->setVolume(100);
    reproductor->play();

    // HUD, galletas y personajes
    crearHUD();

    invulnerableTimer->setSingleShot(true);
    connect(invulnerableTimer, &QTimer::timeout, this, &Juego::finInvulnerabilidad);

    modoEspecialTimer->setSingleShot(true);
    connect(modoEspecialTimer, &QTimer::timeout, this, &Juego::finModoEspecial);

    cargarGalletas();
    crearPersonajes();
    pacman->detenerMovimiento();
    // 🎵 Sonido de fondo de fantasmas
    sonidoFantasma = new QMediaPlayer(this);
    salidaFantasma = new QAudioOutput(this);
    sonidoFantasma->setAudioOutput(salidaFantasma);
    sonidoFantasma->setSource(QUrl("qrc:/Sonidos/fantasma.mp3"));
    salidaFantasma->setVolume(70);
    sonidoFantasma->setLoops(QMediaPlayer::Infinite);  // Repetir infinitamente
    sonidoFantasma->play();
    // Ocultar el mensaje y detener el sonido después de 4.4s
    QTimer::singleShot(4400, this, [=]() {
        mensajeInicio->hide();
        detenerSonidos(); // Libera recursos de audio inicial
        pacman->iniciarAnimacion();
        pacman->reanudarMovimiento();
    });

}

// Muestra puntuación y vidas en la escena
void Juego::crearHUD() {
    textoPuntaje = new QGraphicsTextItem(QString("Puntaje: %1").arg(puntaje));
    textoPuntaje->setDefaultTextColor(Qt::yellow);
    textoPuntaje->setFont(QFont("Arial", 10));
    textoPuntaje->setPos(8, 264);
    escena->addItem(textoPuntaje);

    textoVidas = new QGraphicsTextItem(QString("Vidas: %1").arg(vidas));
    textoVidas->setDefaultTextColor(Qt::white);
    textoVidas->setFont(QFont("Arial", 10));
    textoVidas->setPos(120, 264);
    escena->addItem(textoVidas);
}

// Crea Pacman y los fantasmas en la escena
void Juego::crearPersonajes() {
    pacman = new Pacman(mapa.obtenerMapa(), this);
    escena->addItem(pacman);
    pacman->setFocus();
    actualizarPosicionJugador(pacman->getFila(), pacman->getColumna());

    const std::vector<std::pair<int, int>> posiciones = {
        {14, 13}, {14, 14}, {14, 12}, {14, 15}
    };

    for (const auto& [f, c] : posiciones) {
        Fantasma* fnt = new Fantasma(mapa.obtenerMapa(), this, f, c);
        escena->addItem(fnt);
        fantasmas.push_back(fnt);
    }
}

// Agrega galletas a las posiciones válidas del mapa
void Juego::cargarGalletas() {
    for (int f = 0; f < mapa.filas(); ++f) {
        for (int c = 0; c < mapa.columnas(); ++c) {
            char celda = mapa.getCelda(f, c);
            if (celda == '0' || celda == '2') {
                bool especial = (celda == '2');
                Galleta* g = new Galleta(f, c, 8, especial);
                escena->addItem(g);
                galletas.push_back(g);
                galletasTotales++;
            }
        }
    }
}

// Verifica colisión de Pacman con galletas
void Juego::verificarColisionGalletas(Pacman* pacman) {
    // Obtener todos los elementos con los que colisiona Pacman
    const QList<QGraphicsItem*> colisiones = pacman->collidingItems();

    for (QGraphicsItem* item : colisiones) {
        Galleta* g = dynamic_cast<Galleta*>(item);  // Verificar si el ítem es una galleta
        if (g) {
            // Remover la galleta de la escena
            escena->removeItem(g);

            // Eliminarla del vector de galletas activas
            auto it = std::find(galletas.begin(), galletas.end(), g);
            if (it != galletas.end()) galletas.erase(it);

            // Verificar si es especial
            if (g->esEspecial()) {
                activarModoComerFantasmas();  // Fantasmas se vuelven vulnerables

                // Restaurar estado normal después de 8 segundos
                QTimer::singleShot(8000, this, [this]() {
                    finModoEspecial();
                });

                actualizarPuntaje(20);  // Galleta especial da más puntos
            } else {
                // Galleta normal: reproducir sonido y sumar puntos

                if (!sonidoComer) {
                    sonidoComer = new QMediaPlayer(this);
                    salidaComer = new QAudioOutput(this);
                    sonidoComer->setAudioOutput(salidaComer);
                    sonidoComer->setSource(QUrl("qrc:/Sonidos/comer.mp3"));
                    salidaComer->setVolume(40);
                    sonidoComer->setLoops(QMediaPlayer::Infinite);
                    sonidoComer->play();
                } else if (sonidoComer->playbackState() != QMediaPlayer::PlayingState) {
                    sonidoComer->play();
                }

                actualizarPuntaje(5);  // Galleta normal
            }

            // Aumentar el contador de galletas comidas SIEMPRE
            galletasComidas++;

            // Eliminar el objeto de memoria
            delete g;

            // Verificar si se ganó la partida
            verificarVictoria();

            return;  // Solo procesar una galleta por frame
        }
    }

    // Si no se colisiona con ninguna galleta, pausar sonido de comer (si estaba en reproducción)
    if (sonidoComer && sonidoComer->playbackState() == QMediaPlayer::PlayingState) {
        sonidoComer->pause();  // Pausar en lugar de detener para evitar latencia
    }
}
// Verifica colisión de Pacman con fantasmas
void Juego::verificarColisionFantasma(Pacman* pacman) {
    const QList<QGraphicsItem*> colisiones = pacman->collidingItems();

    for (QGraphicsItem* item : colisiones) {
        Fantasma* f = dynamic_cast<Fantasma*>(item);
        if (!f || !f->isVisible()) continue;

        if (f->estaVulnerable()) {
            f->setVisible(false);
            f->setPos(f->getColumnaInicial() * 8, f->getFilaInicial() * 8);
            f->iniciarRespawn();
            actualizarPuntaje(200);
        } else if (!invulnerable) {
            perderVida();
        }

        break; // Solo uno por colisión
    }
}
// Si ya se comieron todas las galletas, el jugador gana
void Juego::verificarVictoria() {
    if (galletasComidas >= galletasTotales)
        victoria();
}

// Resta una vida y reinicia si no se han acabado
void Juego::perderVida() {
    if (invulnerable || juegoTerminado) return;

    // Detener todos los sonidos del juego
    detenerSonidos();

    if (sonidoFantasma) {
        sonidoFantasma->pause();
        delete sonidoFantasma;
        sonidoFantasma = nullptr;
    }

    // 🎵 Sonido de muerte
    reproductor = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);
    reproductor->setAudioOutput(salidaAudio);
    reproductor->setSource(QUrl("qrc:/Sonidos/muerte.mp3"));
    salidaAudio->setVolume(100);
    reproductor->play();

    // Detener movimiento de todos los fantasmas (sin ocultarlos)
    for (Fantasma* f : fantasmas) {
        f->detenerMovimiento();  // método personalizado que hace timer->stop()
    }

    // Detener y ocultar a Pacman durante los 4 segundos
    if (pacman) {
        pacman->detenerMovimiento();  // método que detiene su QTimer
        pacman->setVisible(false);
    }

    // Actualizar vidas y mostrar
    vidas--;
    textoVidas->setPlainText(QString("Vidas: %1").arg(vidas));
    invulnerable = true;

    // Esperar 4 segundos antes de reiniciar
    QTimer::singleShot(4000, this, [this]() {
        // Reiniciar Pacman
        pacman->reiniciar();
        pacman->setVisible(true);
        pacman->setFlag(QGraphicsItem::ItemIsFocusable);  // ← Necesario si fue eliminado antes
        pacman->setFocus();                               // ← Asegura que reciba teclas
        pacman->reanudarMovimiento();

        // Reiniciar fantasmas
        for (Fantasma* f : fantasmas)
            f->reiniciar();

        // Reanudar sonido de fantasmas
        sonidoFantasma = new QMediaPlayer(this);
        salidaFantasma = new QAudioOutput(this);
        sonidoFantasma->setAudioOutput(salidaFantasma);
        sonidoFantasma->setSource(QUrl("qrc:/Sonidos/fantasma.mp3"));
        salidaFantasma->setVolume(70);
        sonidoFantasma->setLoops(QMediaPlayer::Infinite);
        sonidoFantasma->play();

        invulnerable = false;
    });

    // Verificar si fue la última vida
    if (vidas <= 0) gameOver();
}

// Suma puntos y actualiza texto
void Juego::actualizarPuntaje(int puntosExtra) {
    puntaje += puntosExtra;
    textoPuntaje->setPlainText(QString("Puntaje: %1").arg(puntaje));
}

// Guarda posición lógica de Pacman
void Juego::actualizarPosicionJugador(int fila, int columna) {
    filaJugador = fila;
    columnaJugador = columna;
}

// Devuelve fila actual de Pacman
int Juego::getFilaJugador() const {
    return filaJugador;
}

// Devuelve columna actual de Pacman
int Juego::getColumnaJugador() const {
    return columnaJugador;
}

// Estado de invulnerabilidad temporal tras perder vida
bool Juego::estaInvulnerable() const {
    return invulnerable;
}

// Fin de invulnerabilidad tras delay
void Juego::finInvulnerabilidad() {
    invulnerable = false;
}

// Hace a los fantasmas vulnerables y arranca el timer
void Juego::activarModoComerFantasmas() {
    // Cambiar sprite a vulnerable
    for (Fantasma* f : fantasmas) {
        f->activarModoComestible();
    }

    // Detener sonido normal de fantasmas
    if (sonidoFantasma && sonidoFantasma->playbackState() == QMediaPlayer::PlayingState) {
        sonidoFantasma->pause();
    }
    detenerSonidos();

    // 🎵 Reproducir sonido de poder
    sonidoPoder = new QMediaPlayer(this);
    salidaPoder = new QAudioOutput(this);
    sonidoPoder->setAudioOutput(salidaPoder);
    sonidoPoder->setSource(QUrl("qrc:/Sonidos/poder.mp3"));
    sonidoPoder->setLoops(QMediaPlayer::Infinite);
    salidaPoder->setVolume(90);
    sonidoPoder->play();

}

// Vuelve a poner a los fantasmas en estado normal
void Juego::finModoEspecial() {
    for (Fantasma* f : fantasmas)
        f->restaurarSpriteNormal();
    sonidoPoder->stop();
    sonidoFantasma->play();
}

// Termina el juego por derrota
void Juego::gameOver() {
    // Mostrar mensaje en pantalla
    mensajePantalla = new QLabel("¡Has perdido!", vista);
    mensajePantalla->setStyleSheet("color: red; font-size: 30px; background-color: black; padding: 10px;");
    mensajePantalla->adjustSize();
    mensajePantalla->move((vista->width() - mensajePantalla->width()) / 2,
                          (vista->height() - mensajePantalla->height()) / 2);
    mensajePantalla->show();

    if (sonidoFantasma) {
        sonidoFantasma->stop();
        delete sonidoFantasma;
        sonidoFantasma = nullptr;
    }

    // Sonido de derrota
    reproductor = new QMediaPlayer(this);
    salidaAudio = new QAudioOutput(this);
    reproductor->setAudioOutput(salidaAudio);
    reproductor->setSource(QUrl("qrc:/Sonidos/muerte.mp3"));
    salidaAudio->setVolume(50);
    reproductor->play();

    // Reinicio después de 2 segundos
    QTimer::singleShot(2000, this, [this]() {
        juegoTerminado = true;

        // Detener fantasmas
        for (Fantasma* f : fantasmas)
            f->setVisible(false);

        // Resetear estado del juego
        if (textoPuntaje) {
            escena->removeItem(textoPuntaje);
            delete textoPuntaje;
            textoPuntaje = nullptr;
        }
        vidas = 3;
        puntaje = 0;
        galletasTotales = 0;
        galletasComidas = 0;
        reiniciarNivel();
    });

}

// Termina el juego por victoria
void Juego::victoria() {
    juegoTerminado = true;

    // Mostrar mensaje centrado
    mensajePantalla = new QLabel("¡Ganaste!", vista);
    mensajePantalla->setStyleSheet("color: white; font-size: 26px; background-color: black; padding: 10px;");
    mensajePantalla->adjustSize();
    mensajePantalla->move((vista->width() - mensajePantalla->width()) / 2,
                          (vista->height() - mensajePantalla->height()) / 2);
    mensajePantalla->show();
    // Esperar y reiniciar
    QTimer::singleShot(2000, this, [this]() {
        // Limpieza de escena
        if (pacman) {
            escena->removeItem(pacman);
            delete pacman;
            pacman = nullptr;
        }

        for (Fantasma* f : fantasmas) {
            escena->removeItem(f);
            delete f;
        }
        fantasmas.clear();

        for (Galleta* g : galletas) {
            escena->removeItem(g);
            delete g;
        }
        galletas.clear();

        if (textoPuntaje) {
            escena->removeItem(textoPuntaje);
            delete textoPuntaje;
            textoPuntaje = nullptr;
        }
        if (textoVidas) {
            escena->removeItem(textoVidas);
            delete textoVidas;
            textoVidas = nullptr;
        }

        if (mensajePantalla) {
            delete mensajePantalla;
            mensajePantalla = nullptr;
        }

        // ¡No reiniciar puntaje ni vida! (lo conservamos para niveles o acumulación)
        galletasTotales = 0;
        galletasComidas = 0;
        invulnerable = false;

        if (sonidoFantasma) {
            sonidoFantasma->stop();
            delete sonidoFantasma;
            sonidoFantasma = nullptr;
        }

        // Limpiar y reconstruir escena
        escena->clear();
        mapa.dibujar(escena, 8);

        crearHUD();
        cargarGalletas();
        crearPersonajes();
        pacman->iniciarAnimacion();
        pacman->reanudarMovimiento();

        juegoTerminado = false;
    });
}


void Juego::reiniciarNivel() {
    // Eliminar Pacman
    if (pacman) {
        escena->removeItem(pacman);
        delete pacman;
        pacman = nullptr;
    }

    // Eliminar fantasmas
    for (Fantasma* f : fantasmas) {
        escena->removeItem(f);
        delete f;
    }
    fantasmas.clear();

    // Eliminar galletas
    for (Galleta* g : galletas) {
        escena->removeItem(g);
        delete g;
    }
    galletas.clear();

    // Eliminar textos
    if (textoVidas) {
        escena->removeItem(textoVidas);
        delete textoVidas;
        textoVidas = nullptr;
    }

    // Eliminar mensaje de pantalla si existe
    if (mensajePantalla) {
        delete mensajePantalla;
        mensajePantalla = nullptr;
    }
    //Detener sonido y reestablecer
    detenerSonidos();
    juegoTerminado = false;
    invulnerable = false;
    filaJugador = 1;
    columnaJugador = 1;

    // Volver a cargar el mapa (opcional si ya está cargado)
    escena->clear();  // limpia toda la escena por seguridad
    mapa.dibujar(escena, 8); // redibujar el fondo

    // Volver a crear todo
    crearHUD();
    cargarGalletas();
    crearPersonajes();
    pacman->reanudarMovimiento();
}
void Juego::detenerSonidos() {
    if (reproductor) {
        reproductor->stop();
        delete reproductor;
        reproductor = nullptr;
    }
    if (salidaAudio) {
        delete salidaAudio;
        salidaAudio = nullptr;
    }
    if (sonidoPoder) {
        sonidoPoder->stop();
        delete sonidoPoder;
        sonidoPoder = nullptr;
    }
}



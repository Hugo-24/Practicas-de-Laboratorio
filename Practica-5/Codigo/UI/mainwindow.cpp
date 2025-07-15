#include "mainwindow.h"
#include "Codigo/Core/juego.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    const int tamCelda = 8;
    const int columnas = 29;
    const int filas = 32;
    const int altoHUD = 32;
    const int escala = 2;

    int anchoLogico = tamCelda * columnas;        // 224
    int altoLogico  = tamCelda * filas + altoHUD; // 248

    // Crear vista y escalar visualmente
    vista = new QGraphicsView(this);
    vista->setStyleSheet("background-color: black; border: none;");
    vista->scale(escala, escala);
    vista->setFixedSize(anchoLogico * escala, altoLogico * escala);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Crear juego
    juego = new Juego(vista, this);

    // Layout sin bordes
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(vista);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    setWindowTitle("Pac-Man");
    setFixedSize(vista->width(), vista->height()); // Tamaño final: 448x496
}

MainWindow::~MainWindow() {
    delete juego;
    delete vista;
}

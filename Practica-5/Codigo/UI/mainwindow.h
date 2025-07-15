#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>

class Juego;

/**
 * Clase de la ventana principal del juego Pac-Man.
 * Contiene la vista gráfica y crea el objeto Juego.
 */
class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsView* vista;  // Vista donde se renderiza el juego
    Juego* juego;          // Controlador principal del juego
};

#endif // MAINWINDOW_H

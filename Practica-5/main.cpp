#include <QApplication>
#include "mainwindow.h"

/**
 * Función principal.
 * Inicializa Qt y lanza la ventana principal del juego Pac-Man.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}

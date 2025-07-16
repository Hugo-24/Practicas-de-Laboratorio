#include "ventana_principal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    VentanaPrincipal ventana;
    ventana.showMaximized();  // Se abre en pantalla completa

    return app.exec();
}

#include "galleta.h"
#include <QPixmap>

Galleta::Galleta(int fila, int columna, int tamCelda, bool especial)
    : especial(especial)
{
    QPixmap sprite;

    int ancho = std::max(1, especial ? tamCelda / 2 : tamCelda / 8);
    int alto  = std::max(1, especial ? tamCelda / 2 : tamCelda / 8);

    if (!sprite.isNull()) {
        setPixmap(sprite.scaled(ancho, alto));
    } else {
        if (ancho > 0 && alto > 0) {
            QPixmap fallback(ancho, alto);
            fallback.fill(Qt::white);
            setPixmap(fallback);
        } else {
            qDebug() << "ERROR: dimensiones inválidas para galleta en (" << fila << "," << columna << ")";
        }
    }

    setZValue(1);

    // Ajustar posición para que quede centrada respecto a su tamaño
    qreal offsetX = (tamCelda - ancho) / 1.85;
    qreal offsetY = (tamCelda - alto)  / 1.85;

    setPos(columna * tamCelda + offsetX, fila * tamCelda + offsetY);


}

bool Galleta::esEspecial() const {
    return especial;
}

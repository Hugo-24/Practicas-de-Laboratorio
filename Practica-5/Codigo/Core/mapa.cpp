#include "mapa.h"
#include <QFile>
#include <QTextStream>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QBrush>
#include <QColor>
#include <QDebug>

Mapa::Mapa() {}

bool Mapa::cargarDesdeRecurso(const QString& ruta) {
    QFile archivo(ruta);
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "ERROR: No se pudo abrir el archivo del mapa.";
        return false;
    }

    matriz.clear();
    QTextStream in(&archivo);
    while (!in.atEnd()) {
        QString linea = in.readLine().trimmed();
        if (!linea.isEmpty()) {
            matriz.push_back(linea.toStdString());
        }
    }

    archivo.close();
    return true;
}

const std::vector<std::string>& Mapa::obtenerMapa() const {
    return matriz;
}

char Mapa::getCelda(int fila, int columna) const {
    if (fila < 0 || fila >= filas() || columna < 0 || columna >= columnas()) {
        return '1'; // fuera de rango = pared
    }
    return matriz[fila][columna];
}

bool Mapa::esCeldaLibre(int fila, int columna) const {
    char celda = getCelda(fila, columna);
    return celda == '0';
}

int Mapa::filas() const {
    return static_cast<int>(matriz.size());
}

int Mapa::columnas() const {
    return matriz.empty() ? 0 : static_cast<int>(matriz[0].size());
}

void Mapa::dibujar(QGraphicsScene* escena, int tamCelda) const {
    for (int f = 0; f < filas(); ++f) {
        for (int c = 0; c < columnas(); ++c) {
            char celda = matriz[f][c];  // <- aquí puede crashear si hay columnas disparejas
            qDebug() << "Accediendo a celda" << f << "," << c << "→" << celda;
            if (matriz[f][c] == '1') {
                QGraphicsRectItem* pared = new QGraphicsRectItem(c * tamCelda, f * tamCelda, tamCelda, tamCelda);
                pared->setBrush(QBrush(Qt::blue)); // Pared azul clásica
                pared->setZValue(0); // Detrás de todo
                escena->addItem(pared);
            }
        }
    }
}

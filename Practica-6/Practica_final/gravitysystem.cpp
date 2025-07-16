#include "gravitysystem.h"
#include "body.h"  // Incluir definición completa de Body

GravitySystem::GravitySystem(QObject *parent) : QObject(parent) {}

GravitySystem::~GravitySystem() {
    qDeleteAll(m_bodies);
    m_bodies.clear();
}

void GravitySystem::addBody(Body *body) {
    m_bodies.append(body);
}

void GravitySystem::simulate(double dt, int steps, const QString &outputFile) {
    QFile file(outputFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("No se pudo abrir el archivo de salida");
        return;
    }

    m_currentTime = 0;  // Reiniciar tiempo
    m_dt = dt;         // Establecer paso de tiempo

    QTextStream out(&file);

    // Escribir encabezado
    out << "Tiempo(s)\t";
    for (int i = 0; i < m_bodies.size(); ++i) {
        out << QString("Cuerpo%1_X\tCuerpo%1_Y\t").arg(i+1);
    }
    out << "\n";

    for (int i = 0; i < steps; ++i) {
        calculateForces();
        updatePositions(dt);
        writeStepToFile(file);
    }

    file.close();
}

void GravitySystem::reset() {
    qDeleteAll(m_bodies);
    m_bodies.clear();
    m_currentTime = 0;
}

void GravitySystem::calculateForces() {
    for (Body *body : m_bodies) {
        double totalAx = 0;
        double totalAy = 0;

        for (Body *other : m_bodies) {
            if (body == other) continue;

            double ax, ay;
            body->calculateAcceleration(*other, ax, ay);
            totalAx += ax;
            totalAy += ay;
        }

        body->applyAcceleration(totalAx, totalAy, m_dt);
    }
}

void GravitySystem::updatePositions(double dt) {
    for (Body *body : m_bodies) {
        body->updatePosition(dt);
    }
}

void GravitySystem::writeStepToFile(QFile &file)
{
    QTextStream out(&file);
    out.setRealNumberPrecision(6);  // 6 decimales de precisión
    out.setFieldWidth(10);          // Ancho fijo para alinear columnas

    out << qSetRealNumberPrecision(6) << m_currentTime;

    for (Body *body : m_bodies) {
        out << "\t" << qSetRealNumberPrecision(6) << body->x()
        << "\t" << qSetRealNumberPrecision(6) << body->y();
    }
    out << "\n";

    m_currentTime += m_dt;
}

QString GravitySystem::getCurrentStateString() const
{
    QString state;
    QTextStream out(&state);
    out.setRealNumberPrecision(6);

    // Formato: tiempo + posiciones (X,Y) de cada cuerpo
    out << qSetRealNumberPrecision(6) << m_currentTime;

    for (Body *body : m_bodies) {
        out << "\t" << qSetRealNumberPrecision(6) << body->x()
        << "\t" << qSetRealNumberPrecision(6) << body->y();
    }

    return state;
}

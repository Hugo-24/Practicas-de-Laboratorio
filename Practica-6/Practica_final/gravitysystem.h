#ifndef GRAVITYSYSTEM_H
#define GRAVITYSYSTEM_H

#include <QObject>
#include <QVector>
#include <QFile>

// Añadir estas inclusiones necesarias
#include <QTextStream>
#include <QDebug>

class Body;  // Declaración adelantada

class GravitySystem : public QObject
{
    Q_OBJECT
public:
    explicit GravitySystem(QObject *parent = nullptr);
    ~GravitySystem();

    void addBody(Body *body);
    void simulate(double dt, int steps, const QString &outputFile);
    void reset();
    void calculateForces();
    void updatePositions(double dt);
    int bodyCount() const { return m_bodies.size(); }
    void writeStepToFile(QFile &file);
    QString getCurrentStateString() const;
    double getCurrentTime() const { return m_currentTime; }
    void advanceTime(double dt) { m_currentTime += dt; }

private:
    QVector<Body*> m_bodies;
    double m_currentTime = 0;  // Añadir variable de tiempo
    double m_dt = 1.0;         // Paso de tiempo (según el PDF)
};

#endif // GRAVITYSYSTEM_H

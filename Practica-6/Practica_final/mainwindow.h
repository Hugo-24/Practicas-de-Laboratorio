#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Estructura para datos de cuerpos
struct BodyData {
    double x, y;
    double mass;
    double radius;
    double vx, vy;
    QColor color;

    BodyData() : x(0), y(0), mass(0), radius(0), vx(0), vy(0), color(Qt::blue) {}
    BodyData(double px, double py, double m, double r, double velx, double vely, QColor c = Qt::blue)
        : x(px), y(py), mass(m), radius(r), vx(velx), vy(vely), color(c) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Sistemas predefinidos
    void setupSystem1();
    void setupSystem2();

    // Sistema personalizado
    void showCustomSystemDialog();

    // Control de simulación
    void saveSimulationData();
    void clearScene();
    void updateSimulation();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    class GravitySystem *m_system;
    QTimer *m_timer;
    QList<class BodyGraphicsItem*> m_graphicsItems;

    // Función interna para configuración
    void setupCustomSystem(const QVector<BodyData>& bodiesData);

    QList<QGraphicsEllipseItem*> m_trajectoryDots;  // Para almacenar los puntos de trayectoria
    QColor m_trajectoryColor = Qt::darkGray;       // Color de las trayectorias
};

#endif // MAINWINDOW_H

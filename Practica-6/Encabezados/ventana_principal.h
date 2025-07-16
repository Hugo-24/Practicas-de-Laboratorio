#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QVector>
#include "cuerpo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaPrincipal; }
QT_END_NAMESPACE

// Estructura para guardar datos de un cuerpo personalizado
struct DatosCuerpo {
    float x;
    float y;
    float masa;
    float radio;
    float velocidadX;
    float velocidadY;
    QColor color;
};

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private slots:
    void cargarSistema1();                    // Cargar configuración del Sistema 1
    void cargarSistema2();                    // Cargar configuración del Sistema 2
    void cargarSistemaPersonalizado();        // Abre formulario para crear sistema personalizado
    void iniciarSimulacion();                 // Inicia el temporizador
    void reiniciarSimulacion();               // Limpia todo y detiene simulación
    void guardarDatos();                      // Guarda las trayectorias en un archivo .txt
    void actualizarSimulacion();              // Calcula físicas y mueve los cuerpos

private:
    Ui::VentanaPrincipal *ui;

    QGraphicsScene *escena;                   // Escena donde se dibujan los cuerpos
    QTimer *temporizador;                     // Timer para actualizar en tiempo real

    QVector<Cuerpo*> cuerpos;                 // Lista de cuerpos en simulación
    QVector<QGraphicsEllipseItem*> trayectorias; // Puntos que dibujan la trayectoria

    float deltaTiempo = 1.0f;                 // Paso de tiempo constante

    void limpiarEscena();                     // Borra cuerpos y trayectorias de la escena
    void crearSistema(const QVector<DatosCuerpo>& datos); // Crea los cuerpos en escena según datos
};

#endif // VENTANA_PRINCIPAL_H

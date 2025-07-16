#include "ventana_principal.h"
#include "ui_ventana_principal.h"

#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QColorDialog>
#include <QDialog>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QGraphicsEllipseItem>

const double ESCALA_VISUAL = 1.0 / 40.0;  // Relación física -> escena (como el ejemplo base)

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::VentanaPrincipal),
    escena(new QGraphicsScene(this)),
    temporizador(new QTimer(this)),
    deltaTiempo(1.0f)
{
    ui->setupUi(this);

    // Configurar escena y vista centrada
    ui->graphicsView->setScene(escena);
    escena->setSceneRect(-1000, -1000, 2000, 2000);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.5, -1.5);  // Zoom decente + eje Y hacia arriba
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    // Conexión de botones
    connect(ui->btnSistema1, &QPushButton::clicked, this, &VentanaPrincipal::cargarSistema1);
    connect(ui->btnSistema2, &QPushButton::clicked, this, &VentanaPrincipal::cargarSistema2);
    connect(ui->btnSistemaPersonalizado, &QPushButton::clicked, this, &VentanaPrincipal::cargarSistemaPersonalizado);
    connect(ui->btnIniciar, &QPushButton::clicked, this, &VentanaPrincipal::iniciarSimulacion);
    connect(ui->btnReiniciar, &QPushButton::clicked, this, &VentanaPrincipal::reiniciarSimulacion);
    connect(ui->btnGuardar, &QPushButton::clicked, this, &VentanaPrincipal::guardarDatos);
    connect(temporizador, &QTimer::timeout, this, &VentanaPrincipal::actualizarSimulacion);
}

VentanaPrincipal::~VentanaPrincipal()
{
    limpiarEscena();
    delete ui;
}

// Elimina cuerpos y trayectorias de la escena
void VentanaPrincipal::limpiarEscena()
{
    temporizador->stop();

    for (Cuerpo* c : std::as_const(cuerpos)) {
        escena->removeItem(c);
        delete c;
    }
    cuerpos.clear();

    for (QGraphicsEllipseItem* p : std::as_const(trayectorias)) {
        escena->removeItem(p);
        delete p;
    }
    trayectorias.clear();
}

// Crea los cuerpos del sistema en la escena
void VentanaPrincipal::crearSistema(const QVector<DatosCuerpo>& datos)
{
    limpiarEscena();

    for (const DatosCuerpo& d : datos) {
        auto* cuerpo = new Cuerpo(d.masa, d.radio, d.x, d.y, d.velocidadX, d.velocidadY);
        cuerpo->setBrush(QBrush(d.color));

        // Escalamos el tamaño visual (como en el ejemplo base)
        double radioVisual = std::max(d.radio / 20.0, 4.0);
        cuerpo->setRect(-radioVisual, -radioVisual, 2 * radioVisual, 2 * radioVisual);
        cuerpo->setPos(d.x * ESCALA_VISUAL, d.y * ESCALA_VISUAL);

        cuerpos.append(cuerpo);
        escena->addItem(cuerpo);
    }
}

// Sistema 1 (planeta rojo y dos cuerpos más)
void VentanaPrincipal::cargarSistema1()
{
    QVector<DatosCuerpo> datos = {
        //     x       y       masa   radio  velX  velY   color
        {    0,   -7000,     70,    120,    2,    0,   Qt::blue   }, // Cuerpo 1: satélite azul
        {    0,       0,  70000,    300,    0,    0,   Qt::red    }, // Cuerpo 2: planeta rojo masivo en el centro
        { 4000,    5000,     25,    100, -1.6,  1.2,   Qt::green  }  // Cuerpo 3: otro satélite en órbita
    };

    crearSistema(datos);
}

// Sistema 2 (planeta central con 5 orbitantes)
void VentanaPrincipal::cargarSistema2()
{
    QVector<DatosCuerpo> datos = {
        //     x      y      masa   radio  velX  velY    color
        {     0,      0,   50000,   200,     0,    0,    Qt::red     }, // Cuerpo central (planeta masivo fijo en el centro)
        { -5000,     0,      70,    70,     0,   -2,    Qt::blue    }, // Cuerpo en la izquierda moviéndose hacia abajo
        {  5000,     0,      70,    70,     0,    2,    Qt::green   }, // Cuerpo en la derecha moviéndose hacia arriba
        {     0, -5000,      70,    70,     2,    0,    Qt::yellow  }, // Cuerpo abajo moviéndose hacia la derecha
        {     0,  5000,      70,    70,    -2,    0,    Qt::magenta }  // Cuerpo arriba moviéndose hacia la izquierda
    };

    crearSistema(datos);
}
// Diálogo para crear sistema personalizado
void VentanaPrincipal::cargarSistemaPersonalizado()
{
    bool ok;
    int cantidad = QInputDialog::getInt(this, "Sistema Personalizado", "Número de cuerpos:", 2, 1, 10, 1, &ok);
    if (!ok) return;

    QVector<DatosCuerpo> datos;

    for (int i = 0; i < cantidad; ++i) {
        QDialog dialogo(this);
        dialogo.setWindowTitle(QString("Cuerpo %1").arg(i + 1));
        QFormLayout layout(&dialogo);

        auto* xSpin = new QDoubleSpinBox; xSpin->setRange(-9999, 9999);
        auto* ySpin = new QDoubleSpinBox; ySpin->setRange(-9999, 9999);
        auto* masaSpin = new QDoubleSpinBox; masaSpin->setRange(0.1, 99999);
        auto* radioSpin = new QDoubleSpinBox; radioSpin->setRange(1, 9999);
        auto* velXSpin = new QDoubleSpinBox; velXSpin->setRange(-999, 999);
        auto* velYSpin = new QDoubleSpinBox; velYSpin->setRange(-999, 999);
        auto* colorBtn = new QPushButton("Seleccionar color");

        QColor* color = new QColor(Qt::blue);
        connect(colorBtn, &QPushButton::clicked, this, [=]() {
            QColor elegido = QColorDialog::getColor(*color, this);
            if (elegido.isValid()) *color = elegido;
        });

        layout.addRow("Posición X:", xSpin);
        layout.addRow("Posición Y:", ySpin);
        layout.addRow("Masa:", masaSpin);
        layout.addRow("Radio:", radioSpin);
        layout.addRow("Velocidad X:", velXSpin);
        layout.addRow("Velocidad Y:", velYSpin);
        layout.addRow("Color:", colorBtn);

        QDialogButtonBox* botones = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout.addWidget(botones);
        connect(botones, &QDialogButtonBox::accepted, &dialogo, &QDialog::accept);
        connect(botones, &QDialogButtonBox::rejected, &dialogo, &QDialog::reject);

        if (dialogo.exec() == QDialog::Accepted) {
            datos.append({
                float(xSpin->value()), float(ySpin->value()),
                float(masaSpin->value()), float(radioSpin->value()),
                float(velXSpin->value()), float(velYSpin->value()),
                *color
            });
            delete color;
        } else {
            return;
        }
    }

    crearSistema(datos);
}

// Inicia simulación (solo si no estaba activa)
void VentanaPrincipal::iniciarSimulacion()
{
    if (!temporizador->isActive())
        temporizador->start(16); // 60 FPS aprox
}

// Reinicia todo el sistema
void VentanaPrincipal::reiniciarSimulacion()
{
    limpiarEscena();
}

// Guarda las trayectorias en un archivo
void VentanaPrincipal::guardarDatos()
{
    QString archivo = QFileDialog::getSaveFileName(this, "Guardar datos", "", "Archivos de texto (*.txt)");
    if (archivo.isEmpty()) return;

    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo guardar el archivo.");
        return;
    }

    QTextStream out(&file);
    out << "Tiempo(s)";
    for (int i = 0; i < cuerpos.size(); ++i)
        out << QString("\tCuerpo%1_X\tCuerpo%1_Y").arg(i + 1);
    out << "\n";

    for (int t = 0; t < 10000; ++t) {
        out << t;

        QVector<QVector2D> aceleraciones(cuerpos.size());

        for (int i = 0; i < cuerpos.size(); ++i) {
            QVector2D total(0, 0);
            for (int j = 0; j < cuerpos.size(); ++j)
                if (i != j)
                    total += cuerpos[i]->calcularAceleracion(*cuerpos[j]);
            aceleraciones[i] = total;
        }

        for (int i = 0; i < cuerpos.size(); ++i) {
            cuerpos[i]->actualizarVelocidad(aceleraciones[i], deltaTiempo);
            cuerpos[i]->actualizarPosicion(deltaTiempo);
            cuerpos[i]->setPos(cuerpos[i]->obtenerPosicion().x() * ESCALA_VISUAL,
                               cuerpos[i]->obtenerPosicion().y() * ESCALA_VISUAL);

            QVector2D pos = cuerpos[i]->obtenerPosicion();
            out << "\t" << pos.x() << "\t" << pos.y();
        }

        out << "\n";

        if (t % 100 == 0) {
            qApp->processEvents();
            actualizarSimulacion();
        }
    }

    file.close();
    QMessageBox::information(this, "Éxito", "Datos guardados correctamente.");
}

// Actualiza física y dibuja puntos de trayectoria
void VentanaPrincipal::actualizarSimulacion()
{
    int pasosPorFrame = 8; //  Ajusta este valor para más rapidez
    QVector<QVector2D> aceleraciones(cuerpos.size());

    for (int paso = 0; paso < pasosPorFrame; ++paso) {
        // Calcular aceleraciones
        for (int i = 0; i < cuerpos.size(); ++i) {
            QVector2D total(0, 0);
            for (int j = 0; j < cuerpos.size(); ++j)
                if (i != j)
                    total += cuerpos[i]->calcularAceleracion(*cuerpos[j]);
            aceleraciones[i] = total;
        }

        // Actualizar física
        for (int i = 0; i < cuerpos.size(); ++i) {
            cuerpos[i]->actualizarVelocidad(aceleraciones[i], deltaTiempo);
            cuerpos[i]->actualizarPosicion(deltaTiempo);

            // Actualiza posición visual
            cuerpos[i]->setPos(cuerpos[i]->obtenerPosicion().x() * ESCALA_VISUAL,
                               cuerpos[i]->obtenerPosicion().y() * ESCALA_VISUAL);
        }
    }

    // Dibujar trayectoria solo una vez por frame
    for (int i = 0; i < cuerpos.size(); ++i) {
        auto* punto = new QGraphicsEllipseItem(-1, -1, 2, 2);
        punto->setBrush(cuerpos[i]->brush().color().darker(150));
        punto->setPen(Qt::NoPen);
        punto->setPos(cuerpos[i]->pos());
        escena->addItem(punto);
        trayectorias.append(punto);
    }
}

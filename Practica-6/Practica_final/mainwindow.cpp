#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gravitysystem.h"
#include "body.h"
#include "bodygraphicsitem.h"

#include <QTimer>
#include <QInputDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    m_scene(new QGraphicsScene(this)),
    m_system(new GravitySystem(this)),
    m_timer(new QTimer(this))
{
    ui->setupUi(this);

    // Configurar escena gráfica
    ui->graphicsView->setScene(m_scene);
    m_scene->setSceneRect(-1000, -1000, 2000, 2000);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->scale(1, -1);  // Invertir eje Y

    // Conectar botones
    connect(ui->system1Button, &QPushButton::clicked, this, &MainWindow::setupSystem1);
    connect(ui->system2Button, &QPushButton::clicked, this, &MainWindow::setupSystem2);
    connect(ui->customSystemButton, &QPushButton::clicked, this, &MainWindow::showCustomSystemDialog);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveSimulationData);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::clearScene);

    // Configurar timer
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    m_timer->setInterval(16);  // ~60 FPS
}

MainWindow::~MainWindow()
{
    delete ui;
    clearScene();
    delete m_system;
    delete m_scene;
    delete m_timer;
}

void MainWindow::setupSystem1()
{
    QVector<BodyData> bodiesData = {
        {0, -7000, 70, 120, 2, 0, Qt::blue},
        {0, 0, 70000, 300, 0, 0, Qt::red},
        {4000, 5000, 25, 100, -1.6, 1.2, Qt::green}
    };
    setupCustomSystem(bodiesData);
}

void MainWindow::setupSystem2()
{
    QVector<BodyData> bodiesData = {
        {0, 0, 50000, 200, 0, 0, Qt::red},
        {-5000, 0, 70, 70, 0, -2, Qt::blue},
        {5000, 0, 70, 70, 0, 2, Qt::green},
        {0, -5000, 70, 70, 2, 0, Qt::yellow},
        {0, 5000, 70, 70, -2, 0, Qt::magenta}
    };
    setupCustomSystem(bodiesData);
}

void MainWindow::showCustomSystemDialog()
{
    bool ok;
    int bodyCount = QInputDialog::getInt(this, "Sistema personalizado",
                                         "Número de cuerpos:", 2, 1, 10, 1, &ok);
    if (!ok) return;

    QVector<BodyData> bodiesData;

    for (int i = 0; i < bodyCount; ++i) {
        QDialog dialog(this);
        dialog.setWindowTitle(QString("Cuerpo %1").arg(i+1));
        QFormLayout form(&dialog);

        // Configurar QDoubleSpinBox para posición X (-9999 a 9999)
        QDoubleSpinBox *xSpin = new QDoubleSpinBox(&dialog);
        xSpin->setRange(-9999, 9999);
        xSpin->setDecimals(2);
        xSpin->setSingleStep(100);

        // Configurar QDoubleSpinBox para posición Y (-9999 a 9999)
        QDoubleSpinBox *ySpin = new QDoubleSpinBox(&dialog);
        ySpin->setRange(-9999, 9999);
        ySpin->setDecimals(2);
        ySpin->setSingleStep(100);

        // Configurar QDoubleSpinBox para masa (0.1 a 99999)
        QDoubleSpinBox *massSpin = new QDoubleSpinBox(&dialog);
        massSpin->setRange(0.1, 99999);
        massSpin->setDecimals(2);
        massSpin->setSingleStep(100);

        // Configurar QDoubleSpinBox para radio (1 a 9999)
        QDoubleSpinBox *radiusSpin = new QDoubleSpinBox(&dialog);
        radiusSpin->setRange(1, 9999);
        radiusSpin->setDecimals(1);
        radiusSpin->setSingleStep(10);

        // Configurar QDoubleSpinBox para velocidad X (-999 a 999)
        QDoubleSpinBox *vxSpin = new QDoubleSpinBox(&dialog);
        vxSpin->setRange(-999, 999);
        vxSpin->setDecimals(2);
        vxSpin->setSingleStep(1);

        // Configurar QDoubleSpinBox para velocidad Y (-999 a 999)
        QDoubleSpinBox *vySpin = new QDoubleSpinBox(&dialog);
        vySpin->setRange(-999, 999);
        vySpin->setDecimals(2);
        vySpin->setSingleStep(1);

        QPushButton *colorBtn = new QPushButton("Seleccionar...", &dialog);

        QColor color = Qt::blue;
        connect(colorBtn, &QPushButton::clicked, [&]() {
            color = QColorDialog::getColor(color, &dialog);
        });

        // Organizar formulario
        form.addRow("Posición X (-9999 a 9999):", xSpin);
        form.addRow("Posición Y (-9999 a 9999):", ySpin);
        form.addRow("Masa (0.1 a 99999):", massSpin);
        form.addRow("Radio (1 a 9999):", radiusSpin);
        form.addRow("Velocidad X (-999 a 999):", vxSpin);
        form.addRow("Velocidad Y (-999 a 999):", vySpin);
        form.addRow("Color:", colorBtn);

        QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                 Qt::Horizontal, &dialog);
        form.addRow(&buttons);

        connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        if (dialog.exec() == QDialog::Accepted) {
            bodiesData.append({
                xSpin->value(),
                ySpin->value(),
                massSpin->value(),
                radiusSpin->value(),
                vxSpin->value(),
                vySpin->value(),
                color
            });
        } else {
            return;
        }
    }

    setupCustomSystem(bodiesData);
}

void MainWindow::saveSimulationData()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Guardar trayectorias",
                                                    "",
                                                    "Archivos de texto (*.txt)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para escritura");
        return;
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(6);

    // Escribir encabezado
    out << "Tiempo(s)";
    for (int i = 0; i < m_graphicsItems.size(); ++i) {
        out << QString("\tCuerpo%1_X\tCuerpo%1_Y").arg(i+1);
    }
    out << "\n";

    // Configurar formato numérico
    out.setFieldAlignment(QTextStream::AlignRight);

    // Simular y guardar pasos
    for (int i = 0; i < 10000; ++i) {
        m_system->calculateForces();
        m_system->updatePositions(1.0);

        // Escribir directamente con formato controlado
        out << qSetRealNumberPrecision(6) << m_system->getCurrentTime();

        for (BodyGraphicsItem *item : m_graphicsItems) {
            Body *body = item->body();
            out << "\t" << qSetRealNumberPrecision(6) << body->x()
                << "\t" << qSetRealNumberPrecision(6) << body->y();
        }
        out << "\n";

        // Actualizar tiempo en el sistema
        m_system->advanceTime(1.0);

        // Actualizar UI cada 100 pasos
        if (i % 100 == 0) {
            qApp->processEvents();
            updateSimulation();  // Para ver el progreso visual
        }
    }

    file.close();
    QMessageBox::information(this, "Éxito",
                             "Datos guardados con formato correcto en:\n" + fileName);
}

void MainWindow::clearScene()
{
    m_timer->stop();

    // Limpiar cuerpos
    for (BodyGraphicsItem *item : m_graphicsItems) {
        m_scene->removeItem(item);
        delete item;
    }
    m_graphicsItems.clear();

    // Limpiar trayectorias
    for (QGraphicsEllipseItem *dot : m_trajectoryDots) {
        m_scene->removeItem(dot);
        delete dot;
    }
    m_trajectoryDots.clear();

    m_system->reset();
}

void MainWindow::updateSimulation()
{
    m_system->calculateForces();
    m_system->updatePositions(1.0);

    static int counter = 0;
    if (counter++ % 10 == 0) {
        for (int i = 0; i < m_graphicsItems.size(); ++i) {
            BodyGraphicsItem *item = m_graphicsItems[i];
            QGraphicsEllipseItem *dot = new QGraphicsEllipseItem(-2, -2, 4, 4);
            dot->setPos(item->pos());
            dot->setBrush(QBrush(item->brush().color().darker(150)));
            dot->setPen(Qt::NoPen);
            m_scene->addItem(dot);
            m_trajectoryDots.append(dot);
        }
    }

    // Actualizar posiciones
    for (BodyGraphicsItem *item : m_graphicsItems) {
        item->updatePosition();
    }
}

void MainWindow::setupCustomSystem(const QVector<BodyData>& bodiesData)
{
    clearScene();
    m_system->reset();

    // Configurar color de trayectoria basado en el primer cuerpo
    if (!bodiesData.isEmpty()) {
        m_trajectoryColor = bodiesData.first().color.darker(150);
    }

    for (const BodyData &data : bodiesData) {
        Body *body = new Body(data.x, data.y, data.mass, data.radius, data.vx, data.vy, this);
        m_system->addBody(body);

        BodyGraphicsItem *item = new BodyGraphicsItem(body);
        item->setBrush(QBrush(data.color));

        // Ajustar tamaño visual (más grande)
        double scaledRadius = qMax(data.radius / 20.0, 5.0); // Mínimo 5px de radio
        item->setRect(-scaledRadius, -scaledRadius, scaledRadius*2, scaledRadius*2);

        m_graphicsItems.append(item);
        m_scene->addItem(item);
    }

    m_timer->start();
}

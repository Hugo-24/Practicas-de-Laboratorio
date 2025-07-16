#include "mainwindow.h"
//#include "./ui_mainwindow.h"
#include <QColor>
#include <cstdlib>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //escena = new QGraphicsScene(this);
    //escena->setSceneRect(0, 0, ui->graphicsView->width() - 10, ui->graphicsView->height() - 10);/**/
    escena = new QGraphicsScene(this);
    escena->setSceneRect(-10000, -10000, 20000, 20000); // amplio espacio físico centrado en 0
    ui->graphicsView->centerOn(0, 0);

    ui->graphicsView->setScene(escena);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->adjustSize();

    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::agregarCuerpos() {

    for (cuerpo* c : cuerpos) {
        escena->addItem(c);
    }
}

void MainWindow::simulacion(){

    for (cuerpo* c : cuerpos) {
        c->calcularAceleracion(cuerpos);
        c->actualizarPosicion(ui->graphicsView->width(),ui->graphicsView->height());
    }

    //Escribir en el archivo
    QString line;
    for (int i = 0; i < cuerpos.size(); ++i) {
        line += QString::fromStdString(std::to_string(cuerpos[i]->getX())) + "\t" + QString::fromStdString(std::to_string(cuerpos[i]->getY()));
        if (i != cuerpos.size() - 1) {
            line += "\t";  // Añadir \t solo si no es el último cuerpo
        }else{
            line += "\n";
        }
    }

    QTextStream out(&file);
    out << line;

}

void MainWindow::actualizar(){
    simulacion();
    escena->update();
}


void MainWindow::on_comenzar_button_clicked(){

    if (cuerpos.isEmpty()) return;
    if (!ui->comenzar_button->isEnabled()) return;

    ui->comenzar_button->setEnabled(false);
    ui->pausar_button->setEnabled(true);
    ui->resumir_button->setEnabled(false);
    ui->finalizar_button->setEnabled(true);

    agregarCuerpos();

    ui->graphicsView->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,this, &MainWindow::actualizar);
    timer->start(16);

}


void MainWindow::on_finalizar_button_clicked()
{
    if (!ui->finalizar_button->isEnabled()) return;

    ui->finalizar_button->setEnabled(false);
    ui->pausar_button->setEnabled(false);
    ui->resumir_button->setEnabled(false);
    ui->comenzar_button->setEnabled(true);
    ui->aceptar_button->setEnabled(true);

    timer->stop();

    for (cuerpo* c : cuerpos){
        escena->removeItem(c);
        delete c;
    }
    cuerpos.clear();

    nomArchivo = "";
    numCuerpos = 0;
    file.close();

}


void MainWindow:: on_pausar_button_clicked(){
    if (!ui->pausar_button->isEnabled()) return;

    ui->pausar_button->setEnabled(false);
    ui->comenzar_button->setEnabled(false);
    ui->resumir_button->setEnabled(true);
    ui->finalizar_button->setEnabled(true);
    ui->aceptar_button->setEnabled(false);

    timer->stop();
}

void MainWindow::on_resumir_button_clicked(){
    if (!ui->resumir_button->isEnabled()) return;

    ui->resumir_button->setEnabled(false);
    ui->aceptar_button->setEnabled(false);
    ui->finalizar_button->setEnabled(true);
    ui->comenzar_button->setEnabled(false);
    ui->pausar_button->setEnabled(true);

    timer->start(16);

}

QColor randomColor(){

    int r = rand() % 256; // Valor entre 0 y 255
    int g = rand() % 256;
    int b = rand() % 256;
    return QColor(r, g, b);

}

void MainWindow::on_aceptar_button_clicked(){

    if (!ui->aceptar_button->isEnabled()) return;
    ui->aceptar_button->setEnabled(false);

    nomArchivo = ui->nameFile->text();
    if (ui->nameFile->text().isEmpty()) return;
    nomArchivo+=".txt";

    file.setFileName(nomArchivo);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (!file.isOpen()) return;

}

void MainWindow:: on_agregar_button_clicked(){

    double x = ui->x->value();
    double y = ui->y->value();
    double vx = ui->vx->value();
    double vy = ui->vy->value();
    double m = ui->m->value();
    double r = ui->r->value();

    if (m == 0 || r == 0) return;

    cuerpo* nuevoCuerpo = new cuerpo(x, y, vx, vy, m, r, randomColor());
    cuerpos.append(nuevoCuerpo);
    numCuerpos++;
    ui->cuerposBox->addItem("Cuerpo "+QString::number(numCuerpos));

    ui->x->clear();
    ui->y->clear();
    ui->vx->clear();
    ui->vy->clear();
    ui->m->clear();
    ui->r->clear();

}

void MainWindow:: on_eliminar_button_clicked(){

    int indiceSeleccionado = ui->cuerposBox->currentIndex();
    if (indiceSeleccionado >= 0){
        cuerpos.removeAt(indiceSeleccionado);
        ui->cuerposBox->removeItem(indiceSeleccionado);
    }
}

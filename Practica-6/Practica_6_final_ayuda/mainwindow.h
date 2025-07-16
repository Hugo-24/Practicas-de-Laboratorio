#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include "cuerpo.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene* escena;
    QList<cuerpo*> cuerpos;
    QTimer* timer;

    void agregarCuerpos();
    void simulacion();

    int numCuerpos = 0;

    QFile file;
    QString nomArchivo;

private slots:

    void actualizar();

    void on_aceptar_button_clicked();
    void on_agregar_button_clicked();
    void on_eliminar_button_clicked();
    void on_comenzar_button_clicked();
    void on_finalizar_button_clicked();
    void on_resumir_button_clicked();
    void on_pausar_button_clicked();

};
#endif // MAINWINDOW_H

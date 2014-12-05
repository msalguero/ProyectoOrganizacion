#include "modovisualizacion.h"
//#include "ui_modovisualizacion.h"

ModoVisualizacion::ModoVisualizacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModoVisualizacion)
{
    ui->setupUi(this);
}

ModoVisualizacion::~ModoVisualizacion()
{
    delete ui;
}

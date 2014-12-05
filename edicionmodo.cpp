#include "edicionmodo.h"
#include "ui_edicionmodo.h"
#include "visualizacionmodo.h"
#include "creartabla.h"

EdicionModo::EdicionModo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdicionModo)
{
    ui->setupUi(this);
}

EdicionModo::~EdicionModo()
{
    delete ui;
}

void EdicionModo::on_btnVisualizar_clicked()
{
    //VisualizacionModo VM;
    //VM.setModal(true);
    //VM.exec();
}

void EdicionModo::on_btnCrearTabla_clicked()
{
    //CrearTabla CT;
    //CT.setModal(true);
    //CT.exec();
}

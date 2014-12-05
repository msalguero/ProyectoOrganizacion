#include "modoedicion.h"
#include "ui_modoedicion.h"

ModoEdicion::ModoEdicion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModoEdicion)
{
    ui->setupUi(this);
}

ModoEdicion::~ModoEdicion()
{
    delete ui;
}

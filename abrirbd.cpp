#include "abrirbd.h"
#include "ui_abrirbd.h"

AbrirBD::AbrirBD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AbrirBD)
{
    ui->setupUi(this);
}

AbrirBD::~AbrirBD()
{
    delete ui;
}

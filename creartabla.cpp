#include "creartabla.h"
#include "ui_creartabla.h"
#include "visualizacionmodo.h"
#include "edicionmodo.h"
CrearTabla::CrearTabla(DataBaseManager *gestor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrearTabla)
{
    ui->setupUi(this);

    this->gestor = gestor;
}

CrearTabla::~CrearTabla()
{
    delete ui;
}

void CrearTabla::on_btnVisualizar_clicked()
{
    VisualizacionModo VM(gestor);
    VM.setModal(true);
    VM.exec();

    this->close();
}

void CrearTabla::on_btnEditar_clicked()
{
    EdicionModo EM;
    EM.setModal(true);
    EM.exec();
}

void CrearTabla::on_btnOkNuevoNombreTabla_clicked()
{
    if(ui->txtNombreTabla->text().isEmpty())
        return ;
    ui->btnOkNuevoTipoDatoCampo->setEnabled(true);
    ui->txtNombreCampo->setEnabled(true);
    //ui->txtTamanoCampo->setEnabled(true);

    QString nombre = ui->txtNombreTabla->text();
    QByteArray ba = nombre.toLocal8Bit();
    char *bytesTabla = ba.data();
    char *nombreTabla = (char*)malloc(20);
    memcpy(nombreTabla, bytesTabla, strlen(bytesTabla));
    tablaNueva = gestor->crearNuevaTabla(nombreTabla);
    tablaNueva->agregarCampo(1, "Id", 4);
}

void CrearTabla::on_btnOkNuevoTipoDatoCampo_clicked()
{
    QString nombre = ui->txtNombreCampo->text();
    int tipo = 0;
    int tam = 20;
    if(nombre.isEmpty())
        return ;
    if(ui->comboBox->currentText()== "Entero")
    {
        tipo = 1;
        tam = 4;
    }else{
        tipo = 2;
        tam = 20;
    }
    QByteArray ba = nombre.toLocal8Bit();
    char *bytesCampo = ba.data();
    char *nombreCampo = (char*)malloc(20);
    memcpy(nombreCampo, bytesCampo, strlen(bytesCampo));
    tablaNueva->agregarCampo(tipo, nombreCampo, tam);
    ui->txtNombreCampo->clear();

    ui->comboBox_2->addItem(nombre);
}

void CrearTabla::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int tam = 0;
    if(arg1== "Entero")
        tam = 4;
    else
        tam = 20;

    ui->txtTamanoCampo->setText(QString::number(tam));

}

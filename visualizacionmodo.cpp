#include "visualizacionmodo.h"
#include "ui_visualizacionmodo.h"
#include "edicionmodo.h"
#include "creartabla.h"
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>

VisualizacionModo::VisualizacionModo(QString file, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualizacionModo)
{
    ui->setupUi(this);
    QByteArray ba = file.toLocal8Bit();
    const char *c = ba.data();
    gestor = new DataBaseManager(c);
    tablaActual = NULL;

    gestor->leerMetaDataTablas();
    init();

    connect(ui->twiVizualizacinTabla, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this, SLOT(click_treeWidget(QTreeWidgetItem*,int)));

}

VisualizacionModo::VisualizacionModo(DataBaseManager *gestor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VisualizacionModo)
{
    ui->setupUi(this);

    this->gestor = gestor;
    tablaActual = NULL;

    init();

    connect(ui->twiVizualizacinTabla, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this, SLOT(click_treeWidget(QTreeWidgetItem*,int)));

}

VisualizacionModo::~VisualizacionModo()
{
    delete ui;
}

void VisualizacionModo::on_btnEditar_clicked()
{
    EdicionModo EM;
    EM.setModal(true);
    EM.exec();

}

void VisualizacionModo::on_btnCrearTabla_clicked()
{
    CrearTabla CT(gestor);
    CT.setModal(true);
    CT.exec();

    this->close();
}


void VisualizacionModo::init()
{

    for(int i = 0; i<gestor->cantTablas; i++)
    {
        Table* t = gestor->tablas->Recupera(i);
        QTreeWidgetItem *nombreTabla = new QTreeWidgetItem();
        nombreTabla->setText(0, QString::fromLocal8Bit(t->metaData->nombre));
        //nombreTabla->setIcon(0, QIcon(":/Imagenes/Imgs/1401563677_status-away.png"));
        ui->twiVizualizacinTabla->addTopLevelItem(nombreTabla);
        for(int j = 0; j<t->metaData->cantitdadCampos(); j++)
        {
            QTreeWidgetItem *nombreCampo = new QTreeWidgetItem();
            nombreCampo->setText(0, QString::fromLocal8Bit(t->metaData->metaDataFields->Recupera(j)->nombreCampo));
            //nombreCampo->setIcon(0, QIcon(":/Imagenes/Imgs/1401563677_status-away.png"));
            nombreTabla->addChild(nombreCampo);
        }
    }
}

void VisualizacionModo::mostrarTabla(Table *tabla)
{
    qDebug()<<"Se mando a llamar tabla";
    ui->tblwTablaActual->clearContents();
    ui->tblwTablaActual->clear();
    ui->tblwTablaActual->setRowCount(0);

    int cantCampos = tabla->metaData->cantitdadCampos();
    int cantRegistros = tabla->registros->size;
    ui->tabWidget->setTabText(0, QString::fromLocal8Bit(tabla->metaData->nombre));
    qDebug()<<"ID"<<tabla->metaData->idTabla<<"BloqueDatos"<<tabla->metaData->blqDataI;
    if(cantRegistros == 0)
    {
        gestor->leerRegistrosTabla(tabla->metaData->idTabla);
        cantRegistros = tabla->registros->size;
    }

    ui->tblwTablaActual->setColumnCount(cantCampos);
    ui->tblwTablaActual->setRowCount(cantRegistros);

    qDebug()<<"Se corrio 1 vez la loop"<<cantRegistros;

    QStringList lista;
    for(int i = 0; i<cantCampos; i++)
    {
        lista.append(QString::fromLocal8Bit(tabla->metaData->metaDataFields->Recupera(i)->nombreCampo));
    }

    ui->tblwTablaActual->setHorizontalHeaderLabels(lista);

    for(int i = 0; i<cantRegistros; i++)
    {
        Register* registro = tabla->registros->Recupera(i);

        for(int j = 0; j<cantCampos; j++)
        {
            char* valor = registro->campos->Recupera(j)->valor;
            QString valorCampo="";

            if(tabla->metaData->metaDataFields->Recupera(j)->tipoDato == 1)
            {
                int v;
                memcpy(&v, valor, 4);
                valorCampo = QString::number(v);
            }else
            {
                valorCampo = QString::fromLocal8Bit(valor);
            }
            qDebug()<<valorCampo;
            ui->tblwTablaActual->setItem(i,j,new QTableWidgetItem(valorCampo));
            //ui->tblwTablaActual->item(i,j)->setText(valorCampo);

        }
    }
    //tabla->registros->Anula();

    qDebug()<<"Registros al final d funcion"<<tabla->registros->size;
}

void VisualizacionModo::click_treeWidget(QTreeWidgetItem *item, int column)
{
    if(item == 0)
        return ;
    QByteArray ba = item->text(column).toLocal8Bit();
    const char *c = ba.data();
    Table* tabla = gestor->buscarTabla(c);
    qDebug()<<"Registros al inicio de funcion"<<tabla->registros->size;

    if(tabla == NULL)
        return ;

    mostrarTabla(tabla);
    tablaActual = tabla;
}

void VisualizacionModo::on_pushButton_clicked()
{
    ui->tblwTablaActual->insertRow(ui->tblwTablaActual->rowCount());
}

void VisualizacionModo::on_btnGuardarBase_clicked()
{
    gestor->guardarMetaDataTablas();

}

void VisualizacionModo::on_btnGuardarTabla_clicked()
{
    if(tablaActual == NULL)
        return ;

    int filaRegNuevos = tablaActual->registros->size;

    for(int j = filaRegNuevos; j<ui->tblwTablaActual->rowCount(); j++)
    {
        Register* registroNuevo = new Register(tablaActual->metaData);
        for(int i = 0; i<tablaActual->metaData->cantitdadCampos(); i++)
        {
            MetaDataField* metaCampo = tablaActual->metaData->metaDataFields->Recupera(i);
            QString valor = ui->tblwTablaActual->item(j,i)->text();
            qDebug()<<valor;
            if(metaCampo->tipoDato == 2)
             {
                char* valorCadena = (char*)malloc(20);
                QByteArray ba = valor.toLocal8Bit();
                char *bytesCampo = ba.data();
                memcpy(valorCadena, bytesCampo, strlen(bytesCampo));

                Field* campo = new Field(metaCampo, valorCadena);
                registroNuevo->campos->Agregar(campo);
             }
            else
            {
                int valorEntero = valor.toInt();
                char* entero = (char*)malloc(4);
                memcpy(entero, &valorEntero, 4);
                Field* campo = new Field(metaCampo, entero);
                registroNuevo->campos->Agregar(campo);
            }

        }
        tablaActual->agregarRegistro(registroNuevo);
    }

    gestor->guardarRegistrosTabla(tablaActual->metaData->idTabla);
    gestor->guardarMetaDataTablas();
}

void VisualizacionModo::on_btnBuscarCampos_clicked()
{
    QString text = QInputDialog::getText(this, tr("Busqueda"),
                                             tr("Ingrese Id a buscar:"), QLineEdit::Normal);
    if(tablaActual == NULL || text.isEmpty())
        return;

    ui->tblwTablaActual->clearContents();
    ui->tblwTablaActual->clear();
    ui->tblwTablaActual->setRowCount(1);

    int cantCampos = tablaActual->metaData->cantitdadCampos();
    ui->tblwTablaActual->setColumnCount(cantCampos);

    QStringList lista;
    for(int i = 0; i<cantCampos; i++)
    {
        lista.append(QString::fromLocal8Bit(tablaActual->metaData->metaDataFields->Recupera(i)->nombreCampo));
    }

    ui->tblwTablaActual->setHorizontalHeaderLabels(lista);

    Register* registro = tablaActual->registros->Recupera(0);
    if(registro == NULL)return;

    for(int j = 0; j<cantCampos; j++)
    {
        char* valor = registro->campos->Recupera(j)->valor;
        QString valorCampo="";

        if(tablaActual->metaData->metaDataFields->Recupera(j)->tipoDato == 1)
        {
            int v;
            memcpy(&v, valor, 4);
            valorCampo = QString::number(v);
        }else
        {
            valorCampo = QString::fromLocal8Bit(valor);
        }
        qDebug()<<valorCampo;
        ui->tblwTablaActual->setItem(0,j,new QTableWidgetItem(valorCampo));
    }
}

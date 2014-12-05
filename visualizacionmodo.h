#ifndef VISUALIZACIONMODO_H
#define VISUALIZACIONMODO_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QDebug>
#include "DataBaseManager.h"

namespace Ui {
class VisualizacionModo;
}

class VisualizacionModo : public QDialog
{
    Q_OBJECT

public:
    DataBaseManager* gestor;
    Table* tablaActual;

    explicit VisualizacionModo(QString file, QWidget *parent = 0);
    VisualizacionModo(DataBaseManager* gestor, QWidget *parent = 0);
    ~VisualizacionModo();

    void init();
    void mostrarTabla(Table* tabla);

private slots:
    void on_btnEditar_clicked();

    void on_btnCrearTabla_clicked();

    void click_treeWidget(QTreeWidgetItem * item, int column);

    void on_pushButton_clicked();

    void on_btnGuardarBase_clicked();

    void on_btnGuardarTabla_clicked();

    void on_btnBuscarCampos_clicked();

private:
    Ui::VisualizacionModo *ui;
};

#endif // VISUALIZACIONMODO_H

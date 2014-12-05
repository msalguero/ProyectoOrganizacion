#ifndef CREARTABLA_H
#define CREARTABLA_H

#include <QDialog>
#include "DataBaseManager.h"

namespace Ui {
class CrearTabla;
}

class CrearTabla : public QDialog
{
    Q_OBJECT

public:
    DataBaseManager* gestor;
    Table* tablaNueva;

    explicit CrearTabla(DataBaseManager* gestor, QWidget *parent = 0);
    ~CrearTabla();

private slots:
    void on_btnVisualizar_clicked();

    void on_btnEditar_clicked();

    void on_btnOkNuevoNombreTabla_clicked();

    void on_btnOkNuevoTipoDatoCampo_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::CrearTabla *ui;
};

#endif // CREARTABLA_H

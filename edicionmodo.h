#ifndef EDICIONMODO_H
#define EDICIONMODO_H

#include <QDialog>

namespace Ui {
class EdicionModo;
}

class EdicionModo : public QDialog
{
    Q_OBJECT

public:
    explicit EdicionModo(QWidget *parent = 0);
    ~EdicionModo();

private slots:
    void on_btnVisualizar_clicked();

    void on_btnCrearTabla_clicked();

private:
    Ui::EdicionModo *ui;
};

#endif // EDICIONMODO_H

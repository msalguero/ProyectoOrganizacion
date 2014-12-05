#ifndef ABRIRBD_H
#define ABRIRBD_H

#include <QDialog>

namespace Ui {
class AbrirBD;
}

class AbrirBD : public QDialog
{
    Q_OBJECT

public:
    explicit AbrirBD(QWidget *parent = 0);
    ~AbrirBD();

private:
    Ui::AbrirBD *ui;
};

#endif // ABRIRBD_H

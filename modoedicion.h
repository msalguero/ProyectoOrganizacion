#ifndef MODOEDICION_H
#define MODOEDICION_H

#include <QMainWindow>

namespace Ui {
class ModoEdicion;
}

class ModoEdicion : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModoEdicion(QWidget *parent = 0);
    ~ModoEdicion();

private:
    Ui::ModoEdicion *ui;
};

#endif // MODOEDICION_H

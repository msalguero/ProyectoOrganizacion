#ifndef MODOVISUALIZACION_H
#define MODOVISUALIZACION_H

#include <QMainWindow>

namespace Ui {
class ModoVisualizacion;
}

class ModoVisualizacion : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModoVisualizacion(QWidget *parent = 0);
    ~ModoVisualizacion();

private:
    Ui::ModoVisualizacion *ui;
};

#endif // MODOVISUALIZACION_H

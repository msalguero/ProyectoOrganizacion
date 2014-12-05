#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(int caso,QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_btnMenu_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H

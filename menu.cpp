#include "menu.h"
#include "ui_menu.h"
#include "visualizacionmodo.h"
#include "mainwindow.h"
#include <QFileDialog>

Menu::Menu(int caso, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    if(caso == 0)
        ui->pushButton_3->setText("Crear");
    else
        ui->pushButton_3->setText("Abrir");
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{

}

void Menu::on_pushButton_3_clicked()
{
    VisualizacionModo VM(ui->lineEdit->text());
    VM.setModal(true);
    VM.exec();

    close();
}

void Menu::on_btnMenu_clicked()
{

}

void Menu::on_pushButton_4_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::List);
    if(ui->pushButton_3->text() == "Crear")
        dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec())
        ui->lineEdit->setText(dialog.selectedFiles().at(0));
}

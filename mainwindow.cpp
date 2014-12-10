#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visualizacionmodo.h"
#include "menu.h"
#include "hashtable.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //HashTable tabla(NULL, NULL);

    //tabla.Agregar("21311116", 87);
    //tabla.Buscar("21311116");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_btnMenu_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{
    Menu menu(0);
    menu.setModal(true);
    menu.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    Menu menu(1);
    menu.setModal(true);
    menu.exec();
}

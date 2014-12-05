#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visualizacionmodo.h"
#include "menu.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

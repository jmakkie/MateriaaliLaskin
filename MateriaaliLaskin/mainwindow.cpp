#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbconnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LaskeButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_updateButton_clicked()
{

}


void MainWindow::on_deleteButton_clicked()
{

}


void MainWindow::on_addNewButton_clicked()
{

}


void MainWindow::on_hintaLineEdit_editingFinished()
{

}


void MainWindow::on_MateriaaliLineEdit_editingFinished()
{

}


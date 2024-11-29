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


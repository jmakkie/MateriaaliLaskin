#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dbconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LaskeButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

// values/arvot page functions
void MainWindow::on_arvotAddNewButton_clicked()
{

    QString table, name, value;
    // add check for which table
    table = "Lisat";

    name = ui -> arvotMateriaaliLineEdit -> text();
    value = ui -> arvothintaLineEdit -> text();

    qDebug() << name << value;

    // add checks if data in name and value are correct format etc.
    dbconnection dbconn;
    QString result = saveData(dbconn, table, name, value);

    ui -> label_6 ->setText(result);
}


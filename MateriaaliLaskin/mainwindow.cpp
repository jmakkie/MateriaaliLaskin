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


// laske/calculate/mainwindow
void MainWindow::on_LaskeButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}



// values/arvot page functions
void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString selectedData = "lisat";
    // change dbconn to be a passable/global variable
    dbconnection dbconn;

    //have function return a model
    QSqlQueryModel* model = loadDataToQtableView(dbconn, index, selectedData);
    // update view to show selected table
    ui->arvotTableView->setModel(model);
}

void MainWindow::on_arvotAddNewButton_clicked()
{
    QString table, name, value;

    // add check for which table from selected in the qtableview
    table = "Lisat";

    name = ui -> arvotMateriaaliLineEdit -> text();
    value = ui -> arvothintaLineEdit -> text();

    qDebug() << name << value;

    // add checks if data in name and value are correct format etc.

    // change dbconn to be a passable/global variable
    dbconnection dbconn;
    QString result = saveData(dbconn, table, name, value);

    ui -> label_6 ->setText(result);
}


void MainWindow::on_arvotdeleteButton_clicked()
{
    //implement deleting
}


void MainWindow::on_arvotUpdateButton_clicked()
{
    //implement updating
}

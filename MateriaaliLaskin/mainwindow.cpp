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
void MainWindow::on_LaskeButton_clicked()   // button function for calculating material costs
{
    //implement big maths here
    ui->tabWidget->setCurrentIndex(1);
}



// values/arvot page functions
void MainWindow::on_tabWidget_currentChanged(int index) // function for loading fresh data entries to tables and listview in which ever tab is selected
{
    // sets default data to be loaded. implement index specific default data here?
    QString selectedData = "lisat";

    // change dbconn to be a passable/global variable
    dbconnection dbconn;

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, selectedData);
    QSqlQueryModel* model2 = loadDataToComboBox(dbconn);

    if(index == 2){
        ui->arvotTableView->setModel(model);
        ui->arvotComboBox->setModel(model2);
    }
}

void MainWindow::on_arvotTableView_activated(const QModelIndex &index) // function for placing data from table to textEdit
{
    // use index to get row of table
    int selectedRow = index.row();
    QAbstractItemModel *model = ui -> arvotTableView -> model();

    // pull data from said row
    QVariant variantId = model -> data(model-> index(selectedRow, 0));
    QVariant variantLength = model -> data(model -> index(selectedRow, 1));
    QVariant variantPrice = model -> data(model -> index(selectedRow, 2));
    QString id = variantId.toString();
    QString length = variantLength.toString();
    QString price = variantPrice.toString();

    // todo (again..) fucking , and .

    // slap that data to screen
    ui -> arvotIdLabel -> setText(id);
    ui ->arvotMateriaaliLineEdit -> setText(length);
    ui ->arvothintaLineEdit ->setText(price);


}

void MainWindow::on_arvotComboBox_currentIndexChanged(int index) // function for loading data for selected table
{
    dbconnection dbconn;
    QString selectedData = dbconnection::getTableByIndex(index);

    // query and model to show
    QSqlQueryModel* model = loadDataToQtableView(dbconn, selectedData);
    ui ->arvotTableView->setModel(model);
}

void MainWindow::on_arvotAddNewButton_clicked() // button function for adding new entries to database
{
    QString table, name, value;

    // add check for which table from selected in the qtableview?
    table = "Lisat";

    // get data to be used in the database entry
    name = ui -> arvotMateriaaliLineEdit -> text();
    value = ui -> arvothintaLineEdit -> text();

    // add checks if data in name and value are correct format etc.

    // change dbconn to be a passable/global variable
    dbconnection dbconn;

    // function call for database to create a new entry and display results on a label
    QString result = saveData(dbconn, table, name, value);
    ui -> label_6 ->setText(result);
}

void MainWindow::on_arvotdeleteButton_clicked() //button functions for deleting entries from database
{
    //implement delete
}


void MainWindow::on_arvotUpdateButton_clicked() // button functions for updating entries in databes
{
    //implement updating
}



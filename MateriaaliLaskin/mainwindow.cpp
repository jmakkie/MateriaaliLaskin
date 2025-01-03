#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbconnection.h"
#include "addedmaterial.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //sets certain tableviews to use custom model
    materialTableModel = new materialtablemodel(&materials, this);
    workersTableModel = new workerstablemodel(&worker, this);
    ui -> laskentaAddedtableView -> setModel(materialTableModel);
    ui -> historyMaterialsTableView -> setModel(materialTableModel);
    ui -> laskentaTekjiatTablet -> setModel(workersTableModel);

    //loads data to tables when first opening the application
    firstOpen();
}

MainWindow::~MainWindow()
{
    delete ui;

    // clean up classes
    for (addedmaterial* material : materials){
        delete material;
    }

    for (workers* worker1 : worker) {
        delete worker1;
    }
}

// functions for application use
void MainWindow::firstOpen(){
    // sets default data to be loaded. implement if statements for checking which tab selected and load specifically those
    QString selectedData = "kourut";

    //make lisat not be avaliable on laskenta

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, selectedData);
    QSqlQueryModel* model2 = loadDataToComboBox(dbconn);
    QSqlQueryModel* model3 = loadLisatDataToComboBox(dbconn);

    ui -> laskentaMaterialsTableView->setModel(model);
    ui -> LaskentaComboBox->setModel(model2);
    ui -> laskentaLisatComboBox->setModel(model3);
}

void MainWindow::comboBoxFunction(int comboIndex, int pageIndex){
    QString selectedData = dbconnection::getTableByIndex(comboIndex);

    // query and model to show
    QSqlQueryModel* model = loadDataToQtableView(dbconn, selectedData);
    if(pageIndex == 0){
        ui ->laskentaMaterialsTableView->setModel(model);
    }

    if(pageIndex == 2){
        ui ->arvotTableView->setModel(model);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index) // function for loading fresh data entries to tables and listview in which ever tab is selected
{
    // sets default data to be loaded. implement if statements for checking which tab selected and load specifically those
    QString selectedData = "lisat";

    // change dbconn to be a passable/global variable
    //dbconnection dbconn;

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, selectedData);
    QSqlQueryModel* model2 = loadDataToComboBox(dbconn);

    if(index == 0){
        ui->laskentaMaterialsTableView->setModel(model);
        ui->LaskentaComboBox->setModel(model2);
    }

    if(index == 1){
        //put stuff here
    }

    if(index == 2){
        ui->arvotTableView->setModel(model);
        ui->arvotComboBox->setModel(model2);
    }
}

// laske/calculate/mainwindow
void MainWindow::updateLaskentaAddedTableView(){

}

void MainWindow::on_LaskeButton_clicked()   // button function for calculating material costs
{
    // grabs the easier values
    tekija = ui -> laskentaTekijaLineEdit -> text();
    tunnit = ui -> laskentaHoursLineEdit -> text().toDouble();
    rahakerroin = getMoneyFactor(dbconn);
    tuntihinta = getHourlyPay(dbconn);

    // calculations
    std::vector<double> calc;

    // for loop for looping thorough materials, calculating them and placing them into the list
    for (int i = 0; i < materials.size(); i++){
        // gets values
        addedmaterial* material = materials.at(i);

        QString name = material -> getName();
        QString length = material -> getLength();
        double price = material -> getPrice();
        double amount = material -> getAmount();
        QString lisaName = material -> getLisaName();
        double lisaValue = material -> getLisaValue();

        // calculates gotten values
        double result = price * amount * rahakerroin * lisaValue;

        // adds result to list
        calc.push_back(result);
    }
    urakka = 0;
    // calculate contract pay
    for (std::size_t i = 0; i < calc.size(); i++) {
        urakka += calc[i];
    }

    // calculate hourly wage
    palkka = tuntihinta * tunnit;

    // calculate total
    yht = urakka - palkka;

    // calculate euros for hour
    eurosForHour = yht / tunnit;

    // calculate kta
    kta = tuntihinta + eurosForHour;

    qDebug() << palkka <<  urakka << yht << eurosForHour << kta;

    // change index
    ui->tabWidget->setCurrentIndex(1);

    // call for history setup
    showCalculations();
}

// values/arvot page functions
void MainWindow::on_LaskentaComboBox_activated(int index)
{
    comboBoxFunction(index, 0);
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
    comboBoxFunction(index, 2);
}

void MainWindow::on_arvotAddNewButton_clicked() // button function for adding new entries to database
{
    QString table, name, value;

    // add check for which table from selected in the qtableview?
    table = ui -> arvotComboBox ->currentText();

    qDebug() << table;

    // get data to be used in the database entry
    name = ui -> arvotMateriaaliLineEdit -> text();
    value = ui -> arvothintaLineEdit -> text();

    // add checks if data in name and value are correct format etc.

    // change dbconn to be a passable/global variable
    //dbconnection dbconn;

    // function call for database to create a new entry and display results on a label
    QString result = saveData(dbconn, table, name, value);
    ui -> label_6 ->setText(result);

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, table);
    ui->arvotTableView->setModel(model);

    ui-> arvotIdLabel -> clear();
    ui -> arvotMateriaaliLineEdit -> clear();
    ui-> arvothintaLineEdit ->clear();
}

void MainWindow::on_arvotdeleteButton_clicked() //button functions for deleting entries from database
{
    // get data to be used in the database entry
    QString table, id;
    table = ui -> arvotComboBox ->currentText();
    id = ui -> arvotIdLabel -> text();

    // add checks if data in name and value are correct format etc.

    // change dbconn to be a passable/global variable
    //dbconnection dbconn;

    // function call for database to create a new entry and display results on a label
    QString result = deleteData(dbconn, id, table);
    ui -> label_6 ->setText(result);

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, table);
    ui->arvotTableView->setModel(model);

    ui-> arvotIdLabel -> clear();
    ui -> arvotMateriaaliLineEdit -> clear();
    ui-> arvothintaLineEdit ->clear();
}

void MainWindow::on_arvotUpdateButton_clicked() // button functions for updating entries in databes
{
    // get data to be used in the database entry
    QString table, name, value, id;
    table = ui->arvotComboBox->currentText();
    name = ui -> arvotMateriaaliLineEdit -> text();
    value = ui -> arvothintaLineEdit -> text();
    id = ui -> arvotIdLabel -> text();

    // add checks if data in name and value are correct format etc.

    // change dbconn to be a passable/global variable
    //dbconnection dbconn;

    // function call for database to create a new entry and display results on a label
    QString result = updateData(dbconn, id, table, name, value);
    ui -> label_6 ->setText(result);

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, table);
    ui->arvotTableView->setModel(model);

    ui-> arvotIdLabel -> clear();
    ui -> arvotMateriaaliLineEdit -> clear();
    ui-> arvothintaLineEdit ->clear();
}

void MainWindow::on_arvotUpdateTable_clicked() //funtion for update table
{
    // gets currently loaded table
    QString table, id;
    table = ui -> arvotComboBox -> currentText();

    // change dbconn to be a passable/global variable
    //dbconnection dbconn;

    // call functions to provide models
    QSqlQueryModel* model = loadDataToQtableView(dbconn, table);
    ui->arvotTableView->setModel(model);
}

void MainWindow::on_laskentaMaterialsTableView_activated(const QModelIndex &index)
{
    // use index to get row of table
    int selectedRow = index.row();
    QAbstractItemModel *model = ui -> laskentaMaterialsTableView -> model();

    // pull data from said row
    QString name = ui -> LaskentaComboBox -> currentText();
    QVariant variantLength = model -> data(model -> index(selectedRow, 1));
    QVariant variantPrice = model -> data(model -> index(selectedRow, 2));
    QString length = variantLength.toString();
    QString price = variantPrice.toString();

    // todo (again..) fucking , and .

    // slap that data to screen
    ui -> laskentaProductLabel -> setText(name);
    ui -> laskentaLengthLineEdit -> setText(length);
    ui -> laskentaPriceLineEdit ->setText(price);
}

void MainWindow::on_laskentaLisatComboBox_activated(int index)
{
    QString selectedData = ui -> laskentaLisatComboBox ->currentText();
    QString result = loadLisaValue(dbconn, selectedData);
    ui -> laskentaExtraLineEdit ->setText(result);
}

void MainWindow::on_pushButton_clicked() // button for adding a new material
{
    // get ddata from form fields
    QString name = ui -> laskentaProductLabel ->text();
    QString length = ui ->laskentaLengthLineEdit -> text();
    QString priceString = ui ->laskentaPriceLineEdit -> text();
    double price = priceString.toDouble();
    QString amountString = ui -> laskentaAmountlineEdit -> text();
    double amount = amountString.toDouble();
    QString lisaName = ui ->laskentaLisatComboBox -> currentText();
    QString lisaValueString = ui ->laskentaExtraLineEdit -> text();
    double lisaValue = lisaValueString.toDouble();

    //creating a new object and adding it to the vector
    addedmaterial* newMaterial = new addedmaterial(name, length, price, amount, lisaName, lisaValue);
    //materials.append(newMaterial);

    materialTableModel -> addMaterial(newMaterial);

    qDebug() << "New material added";

    // clear fields
    ui -> laskentaProductLabel -> clear();
    ui -> laskentaLengthLineEdit -> clear();
    ui -> laskentaAmountlineEdit -> clear();
    ui -> laskentaPriceLineEdit -> clear();

    updateLaskentaAddedTableView();
}

// history window functions
void MainWindow::showCalculations(){
    // doubles to strings
    QString palkkaString = QString::number(palkka);
    QString eurosForsHourString = QString::number(eurosForHour);
    QString yhtString = QString::number(yht);
    QString ktaString = QString::number(kta);
    QString tunnitString = QString::number(tunnit);
    QString urakkaString = QString::number(urakka);

    // slap it on screen
    ui -> historyPalkkaLabel -> setText(palkkaString);
    ui -> historyEurosForHourLabel ->setText(eurosForsHourString);
    ui -> historyKtaLabel -> setText(ktaString);
    ui -> historyTekijaLabel -> setText(tekija);
    ui -> historyTunnitLabel -> setText(tunnitString);
    ui -> historyYhtLabel -> setText(yhtString);
    ui -> historyUrakkaLabel -> setText(urakkaString);

    // used materials to screen
}

void MainWindow::on_pushButton_2_clicked() // update added material
{
    addedmaterial* selectedMaterial = materials.at(rowNum);

    //updates materials in QVector with values from fields
    selectedMaterial -> setName(ui -> laskentaProductLabel -> text());
    selectedMaterial -> setLength(ui -> laskentaLengthLineEdit -> text());
    QString string = ui -> laskentaPriceLineEdit -> text();
    double num = string.toDouble();
    selectedMaterial -> setPrice(num);
    string = ui -> laskentaAmountlineEdit -> text();
    num = string.toDouble();
    selectedMaterial -> setAmount(num);
    selectedMaterial -> setLisaName(ui -> laskentaLisatComboBox -> currentText());
    string = ui -> laskentaExtraLineEdit -> text();
    num = string.toDouble();
    selectedMaterial -> setLisaValue(num);

    //update table

    QModelIndex topLeft = materialTableModel->index(rowNum, 0);
    QModelIndex bottomRight = materialTableModel->index(rowNum, materialTableModel->columnCount() - 1);
    emit materialTableModel->dataChanged(topLeft, bottomRight);
}


void MainWindow::on_laskentaAddedtableView_activated(const QModelIndex &index) // display selected material in fields
{
    int row = index.row();
    rowNum = row;

    if (row >= 0 && row < materials.size()) {
        addedmaterial* selectedMaterial = materials.at(row);

        ui -> laskentaProductLabel -> setText(selectedMaterial -> getName());
        double amount = selectedMaterial -> getAmount();
        ui -> laskentaAmountlineEdit -> setText(QString::number(amount));
        ui -> laskentaLengthLineEdit -> setText(selectedMaterial -> getLength());
        ui -> laskentaLisatComboBox -> setCurrentText(selectedMaterial -> getLisaName());
        double lisaValue = selectedMaterial -> getLisaValue();
        ui -> laskentaExtraLineEdit -> setText(QString::number(lisaValue));
        double price = selectedMaterial ->getPrice();
        ui ->laskentaPriceLineEdit -> setText(QString::number(price));
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QString worker2 = ui -> laskentaTekijaLineEdit -> text();
    double hours = ui -> laskentaHoursLineEdit -> text().toDouble();

    workers* newWorker = new workers(worker2, hours);

    workersTableModel -> addWorker(newWorker);

    qDebug() << "New worker added";

    for (workers* worker1 : worker) {
        qDebug() << worker1 ->getWorker();
    }
}

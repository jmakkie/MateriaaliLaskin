#include "dbconnection.h"

dbconnection::dbconnection()
{
    // setting path to database file
    path =QDir::currentPath();
    path += "/database/MateriaaliLaskindb.db";

    // db connecting
    db = QSqlDatabase :: addDatabase("QSQLITE");
    db.setDatabaseName(path);
    if (db.open()) {
        qDebug() << "db connected";
    }
    else {
        qDebug() << "db NOT connected";
        qDebug() << "Error : " << db.lastError();
    }
}

dbconnection::~dbconnection()
{
    db.close();
    QSqlDatabase::removeDatabase(path);
}

QString dbconnection::getDbpath()// returns path to database
{
    return path;
}

// functions for application use.
QSqlQueryModel* loadDataToQtableView(dbconnection &dbconn, QString selectedData) //function to get data from selected table and return it as a model
{
    // query prep
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT * from "+ selectedData +";");

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Data loading failed due to database connection";
        delete model;
        return nullptr;
    }

    // get data from database and place it into the model
    if(qry.exec()){
        qDebug() << "table loaded succesfully from database";
        model -> setQuery(std::move(qry));
    } else {
        qDebug() << "Encountered an error loading table: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        delete model;
        return nullptr;
    }

    return model;
}

QSqlQueryModel* loadDataToComboBox(dbconnection &dbconn) //func to get table names from database and return them as a model
{
    // query prep
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT name FROM sqlite_sequence ORDER BY name ASC;");

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Data loading failed due to database connection";
        delete model;
        return nullptr;
    }

    // get data from database and place it into the model
    if(qry.exec()){
        qDebug() << "Table for comboBox loaded succesfully from database";
        model -> setQuery(std::move(qry));
    } else {
        qDebug() << "Encountered an error loading table names: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        delete model;
        return nullptr;
    }

    return model;
}

// functions for laskenta tab
double getHourlyPay(dbconnection &dbconn){
    QSqlQuery qry;
    QString tunti = "tuntihinta";
    qry.prepare("SELECT hinta FROM muut WHERE pituus = :tuntihinta;");
    qry.bindValue(":tuntihinta", tunti);

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Loading hourly pay failed due to database connection";
        qDebug() << qry.executedQuery();
    }

    double result = 0;
    if(qry.exec()){
        qDebug() << "Success loading hourly pay";

        while (qry.next()) {
            result = qry.value(0).toDouble();
        }

        return result;

    } else {
        qDebug() << "Encountered an error loading hourly pay: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();

        return 0;
    }
}

double getMoneyFactor(dbconnection &dbconn){
    QSqlQuery qry;
    QString raha = "rahakerroin";
    qry.prepare("SELECT hinta FROM muut WHERE pituus = :rahakerroin;");
    qry.bindValue(":rahakerroin", raha);

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Loading money factor failed due to database connection";
        qDebug() << qry.executedQuery();
    }

    double result = 0;
    if(qry.exec()){
        qDebug() << "Success loading money factor";

        while (qry.next()) {
            result = qry.value(0).toDouble();
        }

        return result;

    } else {
        qDebug() << "Encountered an error loading money factor: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();

        return 0;
    }
}

QString loadLisaValue(dbconnection &dbconn, QString name){
    QSqlQuery qry;
    qry.prepare("SELECT hinta FROM lisat WHERE pituus = :name ;");
    qry.bindValue(":name", name);

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Loading price of selected lisa failed due to database connection";
        qDebug() << qry.executedQuery();
        return "Error";
    }

    QString result;
    // get data from database and place it into the model
    if(qry.exec()){
        qDebug() << "Table for lisat comboBox loaded succesfully from database";
        while (qry.next()) {
            result = qry.value(0).toString();
        }
        return result;
    } else {
        qDebug() << "Encountered an error loading price of lisa: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        return "Error";
    }
}

QSqlQueryModel* loadLisatDataToComboBox(dbconnection &dbconn)
{
    // query prep
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT pituus FROM lisat ORDER BY pituus ASC;");

    //connection check
    if (!dbconn.db.isOpen()){
        qDebug() << "Data loading failed due to database connection";
        delete model;
        return nullptr;
    }

    // get data from database and place it into the model
    if(qry.exec()){
        qDebug() << "Table for lisat comboBox loaded succesfully from database";
        model -> setQuery(std::move(qry));
    } else {
        qDebug() << "Encountered an error loading table names: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        delete model;
        return nullptr;
    }

    return model;
}

// functions for arvot/values tab
QString saveData(dbconnection &dbconn, QString table, QString name, QString value) //func for saving data in database
{
    // checks if db was opened correctly (does not check if it is still open, add later)
    if(!dbconn.db.isOpen()){
        qDebug() << "Failed to open database";
        return "Saving failed due to database connection";
    }

    // query prep
    QSqlQuery qry;
    qry.prepare("INSERT INTO "+ table +" (pituus, hinta) VALUES (:name, :value);");
    qry.bindValue(":name", name);
    qry.bindValue(":value", value);

    // query execution
    if(qry.exec()){
        return "Data saved succesfully to database";
    }
    else {
        qDebug() << "Error: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        return "Encountered an error saving data";
    }
}

QString updateData(dbconnection &dbconn, QString id, QString table, QString name, QString value) //function for updating data in database
{
    // checks if db was opened correctly (does not check if it is still open, add later)
    if(!dbconn.db.isOpen()){
        qDebug() << "Failed to open database";
        return "Saving failed due to database connection";
    }

    // query prep
    QSqlQuery qry;
    qry.prepare("UPDATE "+ table +" SET pituus = :name, hinta = :value WHERE id = :id ;");
    qry.bindValue(":name", name);
    qry.bindValue(":value", value);
    qry.bindValue(":id", id);

    // query execution
    if(qry.exec()){
        return "Data updated succesfully";
    }
    else {
        qDebug() << "Error: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        return "Encountered an error updating data";
    }
}

QString deleteData(dbconnection &dbconn, QString id, QString table) //function for data deletion in database
{
    // checks if db was opened correctly (does not check if it is still open, add later)
    if(!dbconn.db.isOpen()){
        qDebug() << "Failed to open database";
        return "Saving failed due to database connection";
    }

    // query prep
    QSqlQuery qry;
    qry.prepare("DELETE FROM "+ table +" WHERE id = "+ id +";");
    //qry.bindValue(":id", id);

    // query execution
    if(qry.exec()){
        return "Data deleted succesfully";
    }
    else {
        qDebug() << "Error: " << dbconn.db.lastError();
        qDebug() << qry.executedQuery();
        return "Encountered an error deleting data";
    }
}

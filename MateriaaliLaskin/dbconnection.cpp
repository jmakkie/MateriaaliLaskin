#include "dbconnection.h"

dbconnection::dbconnection()
{
    // setting path to database file
    path =QDir::currentPath();
    int pos = path.lastIndexOf(QString("/b"));
    path = path.left(pos);
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

// functions for loading data for application use
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
        delete model;
        return nullptr;
    }

    return model;
}

// functions for arvot/values tab
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
        qDebug() << "Table names loaded succesfully from database";
        model -> setQuery(std::move(qry));
    } else {
        qDebug() << "Encountered an error loading table names: " << dbconn.db.lastError();
        delete model;
        return nullptr;
    }

    return model;
}

QString saveData(dbconnection &dbconn, QString table, QString name, QString value)
{
    // checks if db was opened correctly (does not check if it is still open, add later)
    if(!dbconn.db.isOpen()){
        qDebug() << "Failed to open database";
        return "Saving failed due to database connection";
    }

    // query prep
    QSqlQuery qry;
    qry.prepare("INSERT INTO "+ table +" (Pituus, Hinta) VALUES (:name, :value);");
    qry.bindValue(":name", name);
    qry.bindValue(":value", value);

    // query execution
    if(qry.exec()){
        return "Data saved succesfully to database";
    }
    else {
        qDebug() << "Error: " << dbconn.db.lastError();
        return "Encountered an error saving data";
    }
}

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

QString dbconnection::getDbpath()
{
    return path;
}

QSqlQueryModel* loadDataToQtableView(dbconnection &dbconn, int index, QString selectedData)
{
    // query prep
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("SELECT * from "+ selectedData +";");

    if (!dbconn.db.isOpen()){
        qDebug() << "Data loading failed due to database connection";
        delete model;
        return nullptr;
    }

    if(qry.exec()){
        qDebug() << "Data loaded succesfully from database";
        model -> setQuery(std::move(qry));
    } else {
        qDebug() << "Encountered an error loading data: " << dbconn.db.lastError();
        delete model;
        return nullptr;
    }

    // data loading into window with given index
    if(index == 0){        // laske
        delete model;
        return nullptr;
    }
    else if(index == 1){   // historia
        delete model;
        return nullptr;
    }
    else{                  // arvot
        return model;
    }
}

QString saveData(dbconnection &dbconn, QString table, QString name, QString value)
{
    // checks if db was opened correctly (does not check if it is still open, add later)
    if(!dbconn.db.isOpen()){
        qDebug() << "Failed to open database";
        return "Saving failed due to database connection";
    }

    QSqlQuery qry;
    qry.prepare("INSERT INTO "+ table +" (Pituus, Hinta) VALUES (:name, :value);");
    qry.bindValue(":name", name);
    qry.bindValue(":value", value);

    if(qry.exec()){
        return "Data saved succesfully to database";
    }
    else {
        qDebug() << "Error: " << dbconn.db.lastError();
        return "Encountered an error saving data";
    }
}

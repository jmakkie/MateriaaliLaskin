#include "dbconnection.h"

dbconnection::dbconnection() {

    // getting path to database file
    QString path =QDir::currentPath();
    int pos = path.lastIndexOf(QString("/b"));
    path = path.left(pos);

    // db connecting
    db = QSqlDatabase :: addDatabase("QSQLITE");
    db.setDatabaseName(path+"/database/MateriaaliLaskindb.db");
    if (db.open()) {
        qDebug() << "db connected";
    }
    else {
        qDebug() << "db NOT connected";
        qDebug() << "Error : " << db.lastError();
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

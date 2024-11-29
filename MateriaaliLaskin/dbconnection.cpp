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

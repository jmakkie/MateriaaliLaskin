#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class dbconnection
{
public:
    dbconnection();
    friend QString saveData(dbconnection &dbconn, QString table, QString name, QString value);
private:
    QSqlDatabase db;
};

#endif // DBCONNECTION_H

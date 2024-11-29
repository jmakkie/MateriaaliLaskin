#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

class dbconnection
{
public:
    dbconnection();

private:
    QSqlDatabase db;
};

#endif // DBCONNECTION_H

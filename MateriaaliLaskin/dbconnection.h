#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class dbconnection
{
public:
    dbconnection();
    ~dbconnection();
    QString getDbpath();

    friend QSqlQueryModel* loadDataToQtableView(dbconnection &dbconn, int index, QString selectedData);
    friend QString saveData(dbconnection &dbconn, QString table, QString name, QString value);
    friend QString updateData(dbconnection &dbconn, QString table, QString name, QString value);

private:
    QSqlDatabase db;
    QString path;
};

#endif // DBCONNECTION_H

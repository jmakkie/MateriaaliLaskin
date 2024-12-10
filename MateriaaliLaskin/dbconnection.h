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
    static QString getTableByIndex(int index);

    friend QSqlQueryModel* loadDataToQtableView(dbconnection &dbconn, QString selectedData);
    friend QSqlQueryModel* loadLisatDataToComboBox(dbconnection &dbconn);
    friend QSqlQueryModel* loadDataToComboBox(dbconnection &dbconn);
    friend QString loadLisaValue(dbconnection &dbconn, QString name);
    friend QString saveData(dbconnection &dbconn, QString table, QString name, QString value);
    friend QString updateData(dbconnection &dbconn, QString id, QString table, QString name, QString value);
    friend QString deleteData(dbconnection &dbconn, QString id, QString table);

private:
    QSqlDatabase db;
    QString path;
    int id;
};

#endif // DBCONNECTION_H

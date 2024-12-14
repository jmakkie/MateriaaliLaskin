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

    // app wide
    QString getDbpath();
    static QString getTableByIndex(int index);
    friend QSqlQueryModel* loadDataToComboBox(dbconnection &dbconn);
    friend QSqlQueryModel* loadDataToQtableView(dbconnection &dbconn, QString selectedData);

    // values page
    friend QString saveData(dbconnection &dbconn, QString table, QString name, QString value);
    friend QString updateData(dbconnection &dbconn, QString id, QString table, QString name, QString value);
    friend QString deleteData(dbconnection &dbconn, QString id, QString table);

    // calculations page
    friend QSqlQueryModel* loadLisatDataToComboBox(dbconnection &dbconn);
    friend double getHourlyPay(dbconnection &dbconn);
    friend double getMoneyFactor(dbconnection &dbconn);
    friend QString loadLisaValue(dbconnection &dbconn, QString name);

private:
    QSqlDatabase db;
    QString path;
    int id;
};

#endif // DBCONNECTION_H

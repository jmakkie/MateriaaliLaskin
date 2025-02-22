#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnection.h"
#include "addedmaterial.h"
#include "materialtablemodel.h"
#include "workerstablemodel.h"
#include "calculatedtablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // functions for laske/calculate/main window
private slots:
    // functions for application use
    void on_tabWidget_currentChanged(int index);

    // for laske/calculate/main window
    void on_LaskeButton_clicked();
    void on_LaskentaComboBox_activated(int index);
    void on_laskentaMaterialsTableView_activated(const QModelIndex &index);
    void on_laskentaLisatComboBox_activated(int index);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_laskentaAddedtableView_activated(const QModelIndex &index);
    void on_pushButton_3_clicked();

    // for history/laskelmat use

    // for values/arvot
    void on_arvotComboBox_currentIndexChanged(int index);
    void on_arvotTableView_activated(const QModelIndex &index);
    void on_arvotAddNewButton_clicked();
    void on_arvotdeleteButton_clicked();
    void on_arvotUpdateButton_clicked();
    void on_arvotUpdateTable_clicked();

private:
    // application necessary
    Ui::MainWindow *ui;
    dbconnection dbconn;

    QVector<addedmaterial*> materials;
    QVector<workers*> worker;
    QVector<workersCalculated*> workersC;

    // table models
    materialtablemodel *materialTableModel;
    workerstablemodel *workersTableModel;
    calculatedtablemodel *calculatedTableModel;

    // numbers for calculation
    double tuntihinta = 0;
    double rahakerroin = 0;

    // calculation results
    double urakka = 0;
    double yht = 0;
    double kta = 0;
    double eurosForHour = 0;
    double yhteisetTunnit = 0;
    double yhteinenPalkka = 0;
    int rowNum = 0;

    //functions for application use
    void firstOpen();

    // functions for laske/calculate/mainwindow
    void updateLaskentaAddedTableView();

    // functions for history/laskelma
    void showCalculations();



};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbconnection.h"
#include "addedmaterial.h"
#include "materialtablemodel.h"
#include "workerstablemodel.h"
#include "workers.h"

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

    // for values/arvot
    void on_arvotComboBox_currentIndexChanged(int index);
    void on_arvotTableView_activated(const QModelIndex &index);
    void on_arvotAddNewButton_clicked();
    void on_arvotdeleteButton_clicked();
    void on_arvotUpdateButton_clicked();
    void on_arvotUpdateTable_clicked();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_laskentaAddedtableView_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

private:
    // application necessary
    Ui::MainWindow *ui;
    dbconnection dbconn;
    QVector<addedmaterial*> materials;
    QVector<workers*> worker;
    materialtablemodel *materialTableModel;
    workerstablemodel *workersTableModel;

    // numbers for calculation
    double tuntihinta;
    double rahakerroin;

    // calculation results
    double palkka;
    double urakka;
    double tunnit;
    double yht;
    double kta;
    double eurosForHour;
    QString tekija;
    int rowNum;

    //functions for application use
    void firstOpen();
    void comboBoxFunction(int comboIndex, int pageIndex);

    // functions for laske/calculate/mainwindow
    void updateLaskentaAddedTableView();

    // functions for history
    void showCalculations();



};
#endif // MAINWINDOW_H

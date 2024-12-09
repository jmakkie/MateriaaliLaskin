#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
#include "dbconnection.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // functions for application use
    void on_tabWidget_currentChanged(int index);

    // for laske/calculate/main window
    void on_LaskeButton_clicked();

    void on_LaskentaComboBox_activated(int index);

    // for values/arvot
    void on_arvotComboBox_currentIndexChanged(int index);

    void on_arvotTableView_activated(const QModelIndex &index);

    void on_arvotAddNewButton_clicked();

    void on_arvotdeleteButton_clicked();

    void on_arvotUpdateButton_clicked();

    void on_arvotUpdateTable_clicked();

private:

    Ui::MainWindow *ui;

    dbconnection dbconn;

    //functions for application use
    void firstOpen();

    void comboBoxFunction(int comboIndex, int pageIndex);


};
#endif // MAINWINDOW_H

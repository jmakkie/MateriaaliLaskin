#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_tabWidget_currentChanged(int index);

    // laske/calculate/main window
    void on_LaskeButton_clicked();

    // values/arvot
    void on_arvotComboBox_currentIndexChanged(int index);

    void on_arvotAddNewButton_clicked();

    void on_arvotdeleteButton_clicked();

    void on_arvotUpdateButton_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

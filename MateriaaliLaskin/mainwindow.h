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
    void on_LaskeButton_clicked();

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    void on_addNewButton_clicked();

    void on_hintaLineEdit_editingFinished();

    void on_MateriaaliLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

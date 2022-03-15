#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "date.h"
#include <QMainWindow>
#include <QString>
#include <QTableWidget>
#include <QFileDialog>
#include <fstream>
#include <time.h>
#include <QMessageBox>
#include <QFileDialog>
#include<QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    Date *AddArrElements(Date *arr, int size);


private slots:
    void on_addNext_clicked();

    void on_getDataFromFile_clicked();

    void on_addPrev_clicked();

    void on_addIsLeap_clicked();

    void on_addWeak_clicked();

    void on_addDur_clicked();

    void on_addBith_clicked();

    void on_addDate_clicked();

    void on_addCurrDate_clicked();

    void on_saveBtn_clicked();

private:
    Date* dateArr;
    QString fileName;
    int dateSize;
    int dateFromFile;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

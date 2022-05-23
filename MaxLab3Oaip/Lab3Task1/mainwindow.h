#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "doublelist.h"
#include <QFileDialog>
#include <QFile>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addInfo_Tail_clicked();

    void on_out_clicked();

    void on_addInfo_Head_clicked();

    void on_insert_clicked();

    void on_deleteAll_clicked();

    void on_deletenumber_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //void on_sort_clicked();

    void on_open_clicked();

    void on_create_clicked();

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    DoubleList* list;
    QString storage=nullptr;
};
#endif // MAINWINDOW_H

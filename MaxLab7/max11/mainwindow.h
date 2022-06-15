#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "map.h"

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
    void on_find_clicked();

private:

    void show_tree1();

    Ui::MainWindow *ui;

    map<int, QString> m;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QTextEdit>

#include <QFileDialog>

#include "parser.h"

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
    void on_file_clicked();

    void on_input_clicked();

    void start_parsing();

private:
    Ui::MainWindow *ui;

    QString path;

    QTextEdit *inp_code;

    QDialog *inp_wnd;

    QTextEdit *parsing;

};
#endif // MAINWINDOW_H

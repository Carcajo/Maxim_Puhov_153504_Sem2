#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    show_bitset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

inline void MainWindow::show_bitset()
{
    ui->str->setText(b.to_string());

    ui->ull->setText(QString::number(b.to_ulong()));
}


void MainWindow::on_flip__clicked()
{
    b.flip();

    show_bitset();
}


void MainWindow::on_all__clicked()
{
    QString s = b.all() ? "true" : "false";

    ui->statusbar->showMessage(s);
}


void MainWindow::on_any__clicked()
{
    QString s = b.any() ? "true" : "false";

    ui->statusbar->showMessage(s);
}


void MainWindow::on_test__clicked()
{
    QString num_s = ui->test_le->text();

    if (num_s.isEmpty())
        return;

    size_t pos = num_s.toInt();

    QString s = b.test(pos) ? "true" : "false";

    ui->statusbar->showMessage(s);
}


void MainWindow::on_set__clicked()
{

    QString num_s = ui->set_le->text();

    if (num_s.isEmpty())
        return;

    size_t pos = num_s.toInt();

    b.set(pos);

    show_bitset();
}


void MainWindow::on_reset__clicked()
{

    QString num_s = ui->reset_le->text();

    if (num_s.isEmpty())
        return;

    size_t pos = num_s.toInt();

    b.reset(pos);

    show_bitset();
}


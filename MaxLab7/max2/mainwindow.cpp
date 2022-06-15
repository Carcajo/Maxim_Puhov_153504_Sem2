#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 15; i < 22; ++i)
        s.insert(std::move(i));

    for(int i = 15; i < 19; ++i)
        s.insert(std::move(i));

    show_set();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
}


void MainWindow::on_deploy_clicked()
{
    QString depl_key = ui->key_to_deploy->text();

    if (depl_key.isEmpty())
        return;


    int key = depl_key.toInt();

    ui->deploy_text->setText(s.deploy_by(std::move(key)));

}

void MainWindow::show_set()
{
    ui->show_list->clear();

    ui->show_list->setText(s.show());
}


void MainWindow::on_add_clicked()
{

    QString add_key = ui->key_le->text();

    if (add_key.isEmpty())
        return;

    int key = add_key.toInt();

    s.insert(std::move(key));

    show_set();
}


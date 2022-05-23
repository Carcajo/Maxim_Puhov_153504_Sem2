#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setInputMask("999");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outStack()
{
    ui->plainTextEdit->clear();

    for (int i = 0; i < st->getTop(); i++) {
        ui->plainTextEdit->appendPlainText("\n" + QString(QString::number(st->Peek(i + 1))));
    }
}


void MainWindow::on_pushButton_clicked()
{
    if ((ui->lineEdit->text()) == "\0") {
        QMessageBox::critical(this, "Error!", "Nothing to push");
        return;
    }
    int val = (ui->lineEdit->text()).toInt();
    st->push(val);
    outStack();
    ui->lineEdit->clear();
}


void MainWindow::on_popButton_clicked()
{
    if (st->getTop() == 0) {
        QMessageBox::critical(this, "Error!", "Nothing to pop");
        return;
    }
    st->pop();
    outStack();
}


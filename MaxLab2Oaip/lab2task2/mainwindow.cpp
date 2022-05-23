#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pos = 0;
    ui->lineEdit->setInputMask("999");
    //ui->lineEdit_2->setInputMask("999");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::outStack()
{
    ui->plainTextEdit->clear();

    for (int i = 0; i < dl->getLength(); i++) {
        ui->plainTextEdit->appendPlainText(QString::number(dl->getData(i)));
    }


}

void MainWindow::on_pushButton_clicked()
{
    if ((ui->lineEdit->text()) == "\0") {
        QMessageBox::critical(this, "Error!", "Nothing to add");
        return;
    }
    int val = (ui->lineEdit->text()).toInt();
    //dl->insert(pos, val);
    dl->add(val);
    //pos++;
    outStack();
    //ui->lineEdit->clear();
}


void MainWindow::on_pushButton_2_clicked()
{
    if (dl->getLength() == 0) {
        QMessageBox::critical(this, "Error!", "Nothing to delete");
        return;
    }
    dl->popback();
    //pos--;
    outStack();
}


//void MainWindow::on_pushButton_3_clicked()
//{
//    if (dl->getLength() == 0) {
//        QMessageBox::critical(this, "Error!", "Nothing to delete");
//        return;
//    }
//    int erpos = (ui->lineEdit_2->text()).toInt();

//    if (erpos >= dl->getLength()) {
//        QMessageBox::critical(this, "Error!", "Incorrect pos!");
//        return;
//    }
//    dl->erase(erpos);
//    //pos--;
//    outStack();
//}


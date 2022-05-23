#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list.h>
#include <brackets.h>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

#include"stack.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

    StrStack stack;

    auto storage = ui->textEdit->toPlainText();
    auto splitedStr = storage.split('\n');

    for(int i = 0; i < splitedStr.length(); i++){
        for(int j=0; j< splitedStr.at(i).size();j++){
            if(splitedStr.at(i)[j]=='(' || splitedStr.at(i)[j]==')' ||splitedStr.at(i)[j]=='[' || splitedStr.at(i)[j]==']' || splitedStr.at(i)[j]=='{' || splitedStr.at(i)[j] =='}'){
                    stack.push(splitedStr.at(i)[j],i,j);
                    if(stack.fail()){
                        ui->label->setText("Ошибка находиться в " + QString::number(stack.getElem()->i) + " " +QString::number(stack.getElem()->j));
                        return;
                    }
                }
            }
        }
    if(stack.length() != 0){
        ui->label->setText("Ошибка находиться в " + QString::number(stack.getElem()->i+1) + " " +QString::number(stack.getElem()->j+1));
        return;
    }

     ui->label->setText("Успешно!");
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->label_2-> setText("Строка: "+QString::number(cursor.blockNumber()+1)+" Столбец: "+QString::number(cursor.positionInBlock())+1);
}


void MainWindow::on_pushButton_clicked()
{

    auto storage=QFileDialog::getOpenFileName(0,"Выберите файл:", "","*.txt");
    if(storage.isEmpty()){
        return;
    }
    file.setFileName(storage);

    file.open(QIODevice::ReadWrite);
    QTextStream textStream(&file);
    QString line = textStream.readAll();
    ui->textEdit->setPlainText(line);
}


void MainWindow::on_pushButton_3_clicked()
{
    if (!file.isOpen()){
        return;
    }
    QString storage=ui->textEdit->toPlainText();

    QTextStream stream(&file);

    file.resize(0);
    stream<<storage;
    file.close();

}


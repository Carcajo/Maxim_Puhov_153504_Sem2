#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->number->setValidator(new QIntValidator(0, 999999, this));
    ui->date_2->setDate(QDate::currentDate());
    ui->number_2->setValidator(new QIntValidator(0, 999999, this));
    ui->date_3->setDate(QDate::currentDate());
    ui->location->setMaxLength(100);
    ui->location->setMaxLength(100);
    ui->timeEdit->setTime(QTime::currentTime());
    ui->timeEdit_2->setTime(QTime::currentTime());
    ui->freePlaces->setValidator(new QIntValidator(0, 999, this));
    ui->insertNumber->setValidator(new QIntValidator(0, INT32_MAX, this));
    ui->deleteNumber->setValidator(new QIntValidator(0, INT32_MAX, this));

    list=new DoubleList();
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addInfo_Tail_clicked()
{
    if(storage!=nullptr){
        if(ui->number->text().size()>0){
            if(ui->location->text().size()>0){
                if(ui->freePlaces->text().size()>0){
                    list->AddTail(ui->number->text(),ui->date_2->text(), ui->location->text(),ui->timeEdit->text(),ui->freePlaces->text());
                    ui->textBrowser->setText(list->PrintAll());
                    }
                else ui->textBrowser->setText("Введите коректно число свободных мест");
                }
            else ui->textBrowser->setText("Введите коректно пункт назначения");
            }
        else ui->textBrowser->setText("Введите коректно номер поезда");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}

void MainWindow::on_addInfo_Head_clicked()
{

    if(storage!=nullptr){
    if(ui->number->text().size()>0){
        if(ui->location->text().size()>0){
            if(ui->freePlaces->text().size()>0){
                list->AddHead(ui->number->text(),ui->date_2->text(), ui->location->text(),ui->timeEdit->text(),ui->freePlaces->text());
                ui->textBrowser->setText(list->PrintAll());
                }
            else ui->textBrowser->setText("Введите коректно число свободных мест");
            }
        else ui->textBrowser->setText("Введите коректно пункт назначения");
        }
    else ui->textBrowser->setText("Введите коректно номер поезда");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}

void MainWindow::on_out_clicked()
{
    if(storage!=nullptr){
    ui->textBrowser->setText(list->PrintAll());
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}



void MainWindow::on_insert_clicked()
{
    if(storage!=nullptr){
    if(ui->number->text().size()>0){
        if(ui->location->text().size()>0){
            if(ui->freePlaces->text().size()>0){
                if(ui->insertNumber->text().toInt()>0 && ui->insertNumber->text().toInt()<=list->GetCount()+1){
                        list->Insert(ui->number->text(),ui->date_2->text(), ui->location->text(),
                                     ui->timeEdit->text(),ui->freePlaces->text(),ui->insertNumber->text().toInt());
                        ui->textBrowser->setText(list->PrintAll());
                }
                else ui->textBrowser->setText("Введите коректно № добавления");
                }
            else ui->textBrowser->setText("Введите коректно число свободных мест");
            }
        else ui->textBrowser->setText("Введите коректно пункт назначения");
        }
    else ui->textBrowser->setText("Введите коректно номер поезда");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");

}


void MainWindow::on_deleteAll_clicked()
{
    if(storage!=nullptr){
    list->DelAll();
    ui->textBrowser->setText(list->PrintAll());
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_deletenumber_clicked()
{
    if(storage!=nullptr){
    if(ui->deleteNumber->text().toInt()>0 && ui->deleteNumber->text().toInt()<=list->GetCount()){
            list->Del(ui->deleteNumber->text().toInt());
            ui->textBrowser->setText(list->PrintAll());

    }
    else ui->textBrowser->setText("Введите коректно № удаления");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_pushButton_clicked()
{
    if(storage!=nullptr){
    if(list->search(ui->number_2->text(),ui->date_3->text()).size()>5)
    ui->textBrowser->setText(list->search(ui->number_2->text(),ui->date_3->text()));
    else ui->textBrowser->setText("Введите коректные данные поиска");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}


void MainWindow::on_pushButton_2_clicked()
{
    if(storage!=nullptr){
    if(list->search_2(ui->location_2->text(),ui->timeEdit_2->text()).size()>5)
    ui->textBrowser->setText(list->search_2(ui->location_2->text(),ui->timeEdit_2->text()));
    else ui->textBrowser->setText("Введите коректные данные поиска");
    }
else ui->textBrowser->setText("Файл не открыт или не создан");

}

/*
void MainWindow::on_sort_clicked()
{
    if(storage!=nullptr){
        list->sort();
        ui->textBrowser->setText(list->PrintAll());
        }
    else ui->textBrowser->setText("Файл не открыт или не создан");
}
*/

void MainWindow::on_open_clicked()
{
    list->DelAll();
    QString buf[5];
    storage = QFileDialog::getOpenFileName(0,"Выберете файл","","*txt");
    QFile text(storage);
    text.open(QIODevice::ReadOnly);
    while (!text.atEnd()){
        buf[0]=text.readLine();
        if(buf[0][buf[0].size()-1]=='\n') buf[0].remove(buf[0].size()-1,1);
        if(buf[0].size()>6 || buf[0] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            list->DelAll();
            return;
        }
        buf[1]=text.readLine();
        buf[1].remove(10,2);
        if(!QDate::fromString(buf[1],"dd.MM.yyyy").isValid()){
            ui->textBrowser->setText("Неверный файл");
            list->DelAll();
            return;
        }
        buf[2]=text.readLine();
        if(buf[2][buf[2].size()-1]=='\n') buf[2].remove(buf[2].size()-1,1);
        if(buf[1].size()>100 || buf[0] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            list->DelAll();
            return;
        }
        buf[3]=text.readLine();
        buf[3].remove(5,2);
        if(!QTime::fromString(buf[3],"HH:mm").isValid()){
            ui->textBrowser->setText("Неверный файл");
            list->DelAll();
            return;
        }
        buf[4]=text.readLine();
        if(buf[4][buf[4].size()-1]=='\n') buf[4].remove(buf[4].size()-1,1);
        if(buf[4].size()>3 || buf[4] == "\r\n"){
            ui->textBrowser->setText("Неверный файл");
            list->DelAll();
            return;
        }
        text.readLine();
        list->AddTail(buf[0],buf[1],buf[2],buf[3],buf[4]);
    }
    text.close();
    ui->textBrowser->setText("Файл открыт");
}


void MainWindow::on_create_clicked()
{
    storage = QFileDialog::getSaveFileName(0,"Выберете файл","","*.txt");
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    writeStream << list->PrintAllSave();
    text.close();
}


void MainWindow::on_save_clicked()
{
    if(storage!=nullptr){
    QFile text(storage);
    text.open(QIODevice::WriteOnly );
    QTextStream writeStream(&text);
    writeStream << list->PrintAllSave();
    text.close();
    }
else ui->textBrowser->setText("Файл не открыт или не создан");
}



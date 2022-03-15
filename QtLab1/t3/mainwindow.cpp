#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include<QTextBrowser>
#include<QLineEdit>
#include<QWidget>
#include<QString>
#include<QRect>
#include<QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TableWidget->setColumnCount(7);
    QStringList list;
    list << "Date" << "Next day" << "Previous day" << "is Leap" << "Week number" << "Days till birth" << "Duration";
    ui->TableWidget->setHorizontalHeaderLabels(list);

    //ui->lineEditBirth->setInputMask("99.99.9999");
    //ui->lineEditAddItem->setInputMask("99.99.9999");
    dateSize=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addNext_clicked()
{
    for (int i = 0; i < dateSize; i++)
    {
        Date day = dateArr[i].NextDay();
        ui->TableWidget->setItem(i, 1, day.convertIntoTableItem());
    }
}


std::istream& operator>>(std::istream& os, Date& dt) {

    os >> dt.m_day;
    os.ignore();
    os >> dt.m_month;
    os.ignore();
    os >> dt.m_year;
    return os;
}

std::fstream& operator<<(std::fstream& fout, Date& date)
{
    QString day = QString::number(date.m_day);
    QString month = QString::number(date.m_month);
    QString year = QString::number(date.m_year);

    if (date.m_day < 10){
        fout << "0" << date.m_day << ".";
    } else {
        fout << date.m_day << ".";
    }
    if (date.m_month < 10){
        fout << "0" << date.m_month << ".";
    } else {
        fout << date.m_month << ".";
    }
    if (date.m_year < 10){
        fout << "000" << date.m_year;
    } else if (date.m_year < 100){
        fout << "00" << date.m_year;
    } else if (date.m_year < 1000){
        fout << "0" << date.m_year;
    } else {
        fout << date.m_year;
    }
    return fout;
}

void MainWindow::on_addPrev_clicked()
{
    for (int i = 0; i < dateSize; i++)
    {
        Date day = dateArr[i].PreviousDay();
        if (day.m_year == 0) {
            QTableWidgetItem* date = new QTableWidgetItem(QString("31.12.0001 Before our era)"));
            ui->TableWidget->setItem(i, 2, date);
            continue;
        }
        ui->TableWidget->setItem(i, 2, day.convertIntoTableItem());
    }
}


void MainWindow::on_addIsLeap_clicked()
{
    for (int i = 0; i < dateSize; i++)
    {
        bool leap = dateArr[i].IsLeap();
        if (leap)
        {
            QTableWidgetItem* f = new QTableWidgetItem(QString("True"));
            ui->TableWidget->setItem(i, 3, f);
        }
        else
        {
            QTableWidgetItem* f = new QTableWidgetItem(QString("False"));
            ui->TableWidget->setItem(i, 3, f);
        }

    }
}


void MainWindow::on_addWeak_clicked()
{
    for (int i = 0; i < dateSize; i++) {
        short week = dateArr[i].WeekNumber();
        QTableWidgetItem* w = new QTableWidgetItem(QString("%1 w").arg(week));
        ui->TableWidget->setItem(i, 4, w);
    }
}


void MainWindow::on_addDur_clicked()
{
    for (int i = 0; i < dateSize - 1; i++)
    {
        int days = dateArr[i].Duration(dateArr[i + 1]);
        QTableWidgetItem* it = new QTableWidgetItem(QString("%1 d").arg(days));
        ui->TableWidget->setItem(i, 6, it);
    }
}


void MainWindow::on_addBith_clicked()
{
    Date bithadayDate;
//    if(ui->lineEditAddItem->hasAcceptableInput()==false){
//        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
//        return;
//    }

    QString strBirthday = (ui->lineEditBirth->text());
    QString year = strBirthday;
    year.remove(0, 6);
    while (year[0] == '0')
        year.remove(0, 1);

    QString month = strBirthday;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0') month.remove(0, 1);

    QString day = strBirthday;
    day.remove(2, 8);
    if (day[0] == '0') day.remove(0, 1);
    if(month.toInt() > 12  || month.toInt() < 1)
    {
        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
    }
    else if(day.toInt() < 1 || day.toInt() > 31)
    {
        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
    } else {
        bithadayDate.m_day = strBirthday.left(2).toInt();
        bithadayDate.m_month = strBirthday.mid(3, 2).toInt();
        bithadayDate.m_year = strBirthday.right(4).toInt();
        bithadayDate.doValid();
        for (int i = 0; i < dateSize; i++) {
            long day = dateArr[i].DaysTillYourBithday(bithadayDate);
            QTableWidgetItem* d = new QTableWidgetItem(QString("%1 d").arg(day));
            ui->TableWidget->setItem(i, 5, d);
        }
    }

}

Date *MainWindow::AddArrElements(Date *arr, int size)
{
    if (size== 0)
    {
        arr = new Date[size + 1];
    }
    else
    {
        Date* arrTmp = new Date[size + 1];

        for (int i = 0; i < size; i++)
        {
            arrTmp[i] = arr[i];
        }
        delete[] arr;
        arr = arrTmp;
    }
    return arr;
}

void MainWindow::on_addDate_clicked()
{
    Date date;
    if(ui->lineEditAddItem->hasAcceptableInput()==false){
        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
        return;
    }
    QString strDate = (ui->lineEditAddItem->text());
    QString year = strDate;
    year.remove(0, 6);
    while (year[0] == '0')
        year.remove(0, 1);

    QString month = strDate;
    month.remove(0, 3); month.remove(2, 5);
    if (month[0] == '0') month.remove(0, 1);

    QString day = strDate;
    day.remove(2, 8);
    if (day[0] == '0') day.remove(0, 1);
    if(month.toInt() > 12  || month.toInt() < 1)
    {
        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
    }
    else if(day.toInt() < 1 || day.toInt() > 31)
    {
        QMessageBox::critical(this, "Error!", "Input format:\ndd.mm.yyyy");
    }else {
        QString strDate = (ui->lineEditAddItem->text());
        date.m_day = strDate.left(2).toInt();
        date.m_month = strDate.mid(3, 2).toInt();
        date.m_year = strDate.right(4).toInt();
        date.doValid();
        dateArr = AddArrElements(dateArr, dateSize);
        dateArr[dateSize] = date;
        ui->TableWidget->insertRow(dateSize);
        ui->TableWidget->setItem(dateSize, 0, (dateArr[dateSize]).convertIntoTableItem());
        dateSize++;
    }

}


void MainWindow::on_addCurrDate_clicked()
{
    time_t t = time(NULL);
    struct tm* T = localtime(&t);
    Date currentDate(T->tm_mday, T->tm_mon + 1, T->tm_year + 1900);

    dateArr = AddArrElements(dateArr, dateSize);
    dateArr[dateSize] = currentDate;
    ui->TableWidget->insertRow(dateSize);
    ui->TableWidget->setItem(dateSize, 0, (dateArr[dateSize]).convertIntoTableItem());
    dateSize++;
}

void MainWindow::on_getDataFromFile_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file with dates"), "D:/max/t", tr("Text File (*.txt)"));
    if (fileName.isEmpty())
    {
        return;
    }
    std::ifstream file(fileName.toStdString());
    for (dateSize = 0; !file.fail(); dateSize++)
    {
        ui->TableWidget->insertRow(dateSize);
        dateArr = AddArrElements(dateArr, dateSize);
        file >> dateArr[dateSize];
        dateArr[dateSize].doValid();
        ui->TableWidget->setItem(dateSize, 0, (dateArr[dateSize]).convertIntoTableItem());
    }
    dateFromFile = dateSize;
}

void MainWindow::on_saveBtn_clicked()
{
    QString saveName = QFileDialog::getSaveFileName(this, tr("Save a file with dates"), "", tr("Text File (*.txt)"));
    if (saveName.isEmpty())
        return;
    else {
        QFile file(saveName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }
        if (fileName != saveName)
        {
            fileName = saveName;
            std::fstream outFile;
            outFile.open(fileName.toStdString(), std::ios::out);
            for (int i = 0; i < dateSize; i++)
            {
                outFile << dateArr[i] << std::endl;
            }
        } else {
            std::fstream outFile(saveName.toStdString(), std::ios::out|std::ios::app);
            //outFile.seekp(0, std::ios::end);
            for (int i = dateFromFile; i < dateSize; i++)
            {
                outFile << std::endl;
                outFile << dateArr[i];
            }
        }

    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->def->setValidator(new QRegularExpressionValidator(QRegularExpression("[a-e | +-/*()]{255}$")));

    ui->numA->setValidator(new QRegExpValidator(QRegExp("^[0-9.-]{10}&")));
    ui->numB->setValidator(new QRegExpValidator(QRegExp("^[0-9.-]{10}&")));
    ui->numC->setValidator(new QRegExpValidator(QRegExp("^[0-9.-]{10}&")));
    ui->numD->setValidator(new QRegExpValidator(QRegExp("^[0-9.-]{10}&")));
    ui->numE->setValidator(new QRegExpValidator(QRegExp("^[0-9.-]{10}&")));

   // ui->numB->setValidator(new QDoubleValidator);

   // ui->numC->setValidator(new QDoubleValidator);

   // ui->numD->setValidator(new QDoubleValidator);

   // ui->numE->setValidator(new QDoubleValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!correct(ui->def->text())){
        ui->opz->setText("Ошибка");
        return;
    }

    QString tmp = readDefLine(ui->def->text());
    qDebug() << tmp;
    ui->opz->setText(tmp);
    ui->answer->setText(QString::number(getAnswer(tmp)));

}

bool MainWindow::correct(QString str){
    str.remove(' ');
    int index = 1;

    while(index < str.length()){
        if(str[index].isLetter() ||str[index] == '('){
            if(str[index - 1] =='+' ||str[index - 1]=='-' ||str[index - 1] =='*' ||str[index - 1] =='/' || str[index - 1] == '(')
            {
                index++;
                continue;
            }

            qDebug() << str[index-1];
            qDebug() << str[index];
            return false;
        }
        if(str[index] =='+' ||str[index] =='-' ||str[index] =='*' ||str[index] =='/' || str[index] == ')'){
            if(str[index - 1].isLetter() || str[index - 1] == ')'){

                index++;
                continue;
            }

            qDebug() << str[index-1];
            qDebug() << str[index];
            return false;
        }
    }


    int statment = 0;
    for(int i = 0; i < str.length(); i++){
        if(statment < 0){
            return false;
        }
        if(str[i] == '(')
            ++statment;

        if(str[i] == ')')
            --statment;
    }

    if(statment != 0)
        return false;

    return true;
}


double MainWindow::getAnswer(QString str){
    NumStack stack;

    for (int i = 0 ;i < str.length() ; i++ ) {
        if(str[i].isLetter()){
            stack.push(getValue(str[i]));
        }
        else{
            auto secondTmp = stack.eraseValue();

            auto firstTmp = stack.eraseValue();

            if(str[i] == '+')
                stack.push(firstTmp+secondTmp);
            else if(str[i] == '-')
                stack.push(firstTmp-secondTmp);
            else if(str[i] == '*')
                stack.push(firstTmp*secondTmp);
            else
                stack.push(firstTmp/secondTmp);
        }
    }

    double tmp = stack.answer();

    return tmp;
}


double MainWindow::getValue(QChar ch){
    if(ch == 'a')
        return ui->numA->text().toDouble();

    if(ch == 'b')
        return ui->numB->text().toDouble();

    if(ch == 'c')
        return ui->numC->text().toDouble();

    if(ch == 'd')
        return ui->numD->text().toDouble();

    if(ch == 'e')
        return ui->numE->text().toDouble();

    return 0;
}

QString MainWindow::readDefLine(QString str){
    str.remove(' ');

    StrStack stack;
    QString newStr;

    for(int i = 0; i < str.length();i++){

        if(str[i].isLetter()){
            newStr.push_back(str[i]);
        }
        else{
            if(str[i] == '(' ){
                stack.push(str[i]);
                continue;
            }
            if(str[i] == ')' ){
                newStr.push_back(stack.returnPrev(str[i]));
                continue;
            }

            newStr.push_back(stack.returnPrev(str[i]));
            stack.push(str[i]);
        }
    }

    newStr.push_back(stack.returnLasts());

    return newStr;
}

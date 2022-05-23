#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //std::cout << "kokoko" << std::endl;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_triggered()
{

}

void MainWindow::updateText() {
    /*
    QString s;
    for (int i = 0; i < v.size(); i++) {
        s += QString::number(v[i]) + "\n";
    }
    ui->textEdit->setText(s);
    */
    ht.print(ui->textEdit);
}

void MainWindow::on_actionErase_triggered()
{

}

void MainWindow::on_actionCount_triggered()
{

}

void MainWindow::on_actionAdd_random_triggered()
{

}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok = false;
    int key = QInputDialog::getInt(this, "Ключ", "Введите ключ: ", 0, 0, 1000000, 1, &ok);
    if (ok)
    {
        ht.push(key);
        v.push_back(key);
        updateText();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok = false;
    int key = QInputDialog::getInt(this, "Ключ", "Введите ключ: ", 0, 0, 1000000, 1, &ok);
    if (ok)
    {
        ht.erase(key);
        v.erase_key(key);
        updateText();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    bool ok = false;
    int number = QInputDialog::getInt(this, "Случайное добавление", "Введите количество добавляемых чисел: ", 0, 0, 100000, 1, &ok);
    if (ok)
    {
        QRandomGenerator generator;
        for (int i = 0; i < number; i++)
        {
            int key = generator.bounded(0, 10000);
            ht.push(key);
            v.push_back(key);
        }
        updateText();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString ans = QString::number(ht.getValue());
    QMessageBox msgBox;
    msgBox.setText(ans);
    msgBox.exec();
}

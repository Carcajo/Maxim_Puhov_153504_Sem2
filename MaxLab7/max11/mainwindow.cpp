#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<int> nums{10,40,30,60,90,70,20,50,80,100};

    for (auto num : nums)
        m.insert(std::make_pair(num / 10, QString::number(num + 1)));

    show_tree1();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_find_clicked()
{
    QString key = ui->key_le->text();

    if (key.isEmpty())
        return;

    int key_ = key.toInt();

    QString val = m[std::move(key_)];

    ui->statusbar->showMessage(val);

    show_tree1();
}

void MainWindow::show_tree1()
{
    ui->show_tree->setText("\n\n");

    ui->show_tree->clear();

    ui->show_tree->setText(m.print());

    QString str;

    for (map<int, QString>::iterator it = m.begin(); it != m.end(); ++it) {

        str += QString::number((*it).first);
        str += " ";
        str += ((*it).second);
        str += "\n\n";
    }

    ui->iterators->setText("\n\n");

    ui->iterators->setText(str);
}


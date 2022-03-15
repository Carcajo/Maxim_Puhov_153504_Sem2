#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <QFileDialog>
#include <QTextStream>

#include "book.h"

MainWindow::MainWindow(QWidget *parent)  : QMainWindow(parent)  , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  QVector <Book> books(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::on_pushButton_clicked()// добавление
{

    if (ui->name->text().length()==0 ||
            !!ui->author->text().length()==0 ||
            !!ui->year->text().length()==0 ||
            !!ui->publication->text().length()==0 ||
            !!ui->pages->text().length()==0
        ) return false;


    Book *thisbook=new Book
            (
                ui->name->text(),
                //ui->author->toPlainText(),
                ui->author->text(),
                ui->year->text(),
                ui->publication->text(),
                ui->pages->text()
            );
  ui->name->clear();
  ui->author->clear();
  ui->year->clear();
  ui->publication->clear();
  ui->pages->clear();
  books.append(*thisbook);
  RenderList();
  return true;
}

void MainWindow::on_pushButton_2_clicked()// удаление
{
    if (ui->listBooks->currentRow ()<0) return ;
    books.remove(ui->listBooks->currentRow());
    RenderList();
   //ui->tmp->setPlainText(ui->listBooks->item(ui->listBooks->currentRow ())->text() );
}


void MainWindow::on_pushButton_4_clicked()// редактирование
{
    if (ui->listBooks->currentRow ()<0) return ;
    //QStringList list=ui->listBooks->item(ui->listBooks->currentRow ())->text().split(" ; ");
    QStringList list=(books[ui->listBooks->currentRow ()].getFull()).split(" ; ");
    //fio ; name ; year ; qwe ; pages ;
    ui->name->setText(list[1]);
    //ui->author->setPlainText(list[0]);
    ui->author->setText(list[0]);
    ui->year->setText(list[2]);
    ui->publication->setText(list[3]);
    ui->pages->setText(list[4]);
    books.remove(ui->listBooks->currentRow());
    RenderList();

}


void MainWindow::on_pushButton_5_clicked()// поиск
{

}


void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)// поиск по автору
{

}


void MainWindow::on_textBrowser_2_anchorClicked(const QUrl &arg1)// поиск по названию
{

}

void MainWindow::RenderList()
{
    ui->listBooks->clear();
    for (int i=0; i<books.size();i++ ) {
        ui->listBooks->addItem(books[i].getFull());

    }
}


bool MainWindow::on_pushButton_3_clicked()
{
    QString filename=QFileDialog::getOpenFileName(0,"Select File to Open","","*.txt");
    if (filename.length()==0) return false;
    QFile file (filename)    ;
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
          return false;
      books.clear();
      while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList list = (line.trimmed()).split(" ; ");
          if(list.count()!=5) return false;

              Book *thisbook=new Book
                      (
                          list[1],
                          list[0],
                          list[2],
                          list[3],
                          list[4]
                      );


            books.append(*thisbook);
      }
      file.close();
      RenderList();
     return true;
}


void MainWindow::on_pushButton_6_clicked()
{
    if (ui->listBooks->count()==0) return;
    QString filename = QFileDialog::getSaveFileName(0, "Save file", "", "*.txt");
    if (filename.length()==0) return ;
    if (filename.length()<=4) return ;
    QFile file (filename)    ;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return ;
    QTextStream stream(&file);

    for (int i=0;i<books.count();i++)
               stream << books[i].getFull() <<"\n";
    file.close();

}

void MainWindow::on_find_cursorPositionChanged()
{
    //if (ui->find->toPlainText().isEmpty()) return;
    for (int i=0;i<books.count();i++)
         ui->listBooks->item(i)->setHidden(
//               !(books[i].getAuthor().contains(ui->find->toPlainText()) ||
//                books[i].getYear().contains(ui->find->toPlainText()))
                     !(books[i].getFull().contains(ui->find->toPlainText()))
                     );
}




#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsScene>
#include<solder.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    tmr = new QTimer(this);
    /*
    tmr->start(1000/200);*/
    scene = new QGraphicsScene(0,0,1500,750,parent);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scene->setSceneRect(0,0,1000,1000);

    Solder = new solder(x,y,scene);
    Solder->draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

//    if (moveY_up)
//        if(y>=-50)
//        y -= 0.5;

//    if (moveX_right)
// if(x>=-20) x-=0.1;
//      if(x>=-30) x+=0.5;

//    if (moveY_down)
//        if(y<=80)
//            y+=0.5;

//    if(moveX_left)
//        //if(x >= -50)
//            x-=0.5;

//QPainter painter;
//painter.begin(this);
//QPen pen;
//pen.setColor(Qt::darkGreen);
//pen.setWidth(4);
//painter.setPen(pen);
//painter.setBrush(QBrush("#c56c00"));
//painter.drawEllipse(130+x,60+y,60,60);
//painter.setBrush(Qt::darkGreen);
//painter.drawRect(110+x,120+y,100,160);
//painter.setBrush(Qt::yellow);
//painter.drawRect(145+x,120+y,30,160);
//painter.drawLine(110+x,120+y,85+x,190+y);
//painter.drawLine(85+x,190+y,60+x+x1,260+y+y1);
//painter.drawLine(210+x,120+y,260+x,260+y);
//painter.drawLine(110+x,280+y,80+x,400+y);
//painter.drawLine(210+x,280+y,250+x,400+y);

//painter.end();
}


void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    Solder->moveRight();
    Solder->draw();
}


void MainWindow::on_pushButton_2_clicked()// вверх
{

    static int clicked = 1;

if (clicked % 2)
    connect(tmr, SIGNAL(timeout()), this, SLOT(repaint()));

else
    disconnect(tmr, SIGNAL(timeout()), this, SLOT(repaint()));

++clicked;

}


void MainWindow::on_pushButton_3_clicked()// вниз
{
     static int clicked = 1;

 if (clicked % 2)
     connect(tmr, SIGNAL(timeout()), this, SLOT(repaint()));

 else
     disconnect(tmr, SIGNAL(timeout()), this, SLOT(repaint()));

 ++clicked;

 }



void MainWindow::on_pushButton_4_clicked()// влево
{   scene->clear();
  Solder->moveLeft();
  Solder->draw();
}


void MainWindow::on_pushButton_5_clicked()
{

    scene->clear();

    if(!handIsUp){
        Solder->up();
        Solder->draw();
        handIsUp = true;
    }
    else
    {
        Solder->down();
        Solder->draw();
        handIsUp = false;
    }
}


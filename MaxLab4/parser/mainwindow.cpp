#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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


void MainWindow::on_file_clicked()
{
    path = QFileDialog::getOpenFileName(this, "", "C:/Users/admin/Desktop/", "CPP files (*.cpp);");

    if (path.isEmpty())
        return;

    QFont font;
    font.setPixelSize(20);

    QDialog *wnd = new QDialog(this);

    wnd->resize(1400, 1000);

    QTextEdit *code = new QTextEdit(wnd);

    code->resize(600, 1000);

    code->setFont(font);

    QFile f(path);

    f.open(QFile::ReadOnly);

    QString buf = f.readAll();

    path = "";

    f.close();

    wnd->setModal(true);

    code->setText(buf);

    QTextEdit *parsing_ = new QTextEdit(wnd);

    parsing_->resize(800, 1000);

    parsing_->setFont(font);

    parsing_->move(600, 0);

    std::string input = buf.toStdString();

    parser prs(input.c_str());

    prs.parse();

    parsing_->setFont(font);

    parsing_->setText(prs.get_info());

    wnd->show();

}


void MainWindow::on_input_clicked()
{
    QFont font;
    font.setPixelSize(20);

    inp_wnd = new QDialog(this);

    inp_wnd->resize(1400, 600);

    inp_code = new QTextEdit(inp_wnd);

    QPushButton *parse_btn = new QPushButton("тык", inp_wnd);

    parse_btn->setFont(font);

    parse_btn->move(630, 500);

    inp_code->resize(600, 400);

    inp_code->setFont(font);

    path = "";

    inp_wnd->setModal(true);

    parsing = new QTextEdit(inp_wnd);

    parsing->resize(800, 400);

    parsing->setFont(font);

    parsing->move(600, 0);

    parsing->setDisabled(true);

    connect(parse_btn, SIGNAL(clicked()), this, SLOT(start_parsing()));

    //std::string input = buf.toStdString();

    //parser prs(input.c_str());

    //prs.parse();

    parsing->setFont(font);

    //parsing->setText(prs.get_info());

    inp_wnd->show();
}

void MainWindow::start_parsing()
{

    QString code = inp_code->toPlainText();

    if (code.isEmpty())
        return;

    parsing->clear();

    parsing->setEnabled(true);

    std::string _code = code.toStdString();

    parser prs(_code.c_str());

    prs.parse();

    parsing->setText(prs.get_info());

}


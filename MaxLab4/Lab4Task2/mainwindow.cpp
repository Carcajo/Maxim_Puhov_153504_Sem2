#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(255, 255, 0));

    setPalette(pal);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_clicked()
{
    close();
}


void MainWindow::on_memcpy_clicked()
{
    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(400, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    char str1[] = "Строка для примера";

    char str2[40];

    _memcpy(str2, str1, _strlen(str1) + 1);

    QString STR2(str2);

    example->setText("char str1[] = 'Строка для примера';\nchar str2[40];\n\nmemcpy(str2, str1, strlen(str1) + 1);\n\n\n\n"
                     "\tРезультат:\n\nstr2 = " + STR2);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_memmove_clicked()
{

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(850, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText("char str[] = memmove может оказаться очень полезной функцией..............;\n\nmemmove (str + 49, str + 38, 47);\n\n\n\n"
                     "\tРезультат:\n\nstr = memmove может оказаться очень очень полезной функцией…");

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_strcpy_clicked()
{
    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(600, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    char str3[80];

    _strcpy(str3, "копирование завершено");

    QString STR2(str3);

    example->setText("char str[80];\n\n strcpy(str3, 'копирование завершено');\n\n\n\n"
                     "\tРезультат:\n\nstr = " + STR2);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_strncpy_clicked()
{
    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(400, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    char str1[] = "Кола или мб пиво";
    char str2[10];

    _strncpy(str2, str1, 8);

    str2[8] = '\0';

    QString STR2(str2);

    example->setText("char str1[] = 'Кола или мб пиво';\nchar str2[10];\n\nstrncpy(str2, str1, 8);\n\n\n\n"
                     "\tРезультат:\n\nstr = " + STR2);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_strcat_clicked()
{
    char str[100];
        _strcat( str, "Эти ");
        _strcat( str, "строки ");
        _strcat( str, "объединены ");

        QDialog* wnd = new QDialog(this);

        wnd->setAutoFillBackground(true);

        QPalette pal;
        pal.setBrush(QPalette::Background, QColor(30, 144, 255));

        wnd->setPalette(pal);

        wnd->resize(400, 400);

        wnd->setModal(true);

        QLabel *example = new QLabel(wnd);

        QFont font;
        font.setPixelSize(22);

        QString STR2(str);

        example->setText("char str[100];\n\n_strcat( str, 'Эти ');\n_strcat( str, 'cтроки ');\n_strcat( str, 'объединены ');\n\n\n\n"
                         "\tРезультат:\n\nstr = Эти строки объединены");

        example->move(30, 40);

        example->setFont(font);

        example->adjustSize();


        wnd->show();
    }


void MainWindow::on_strncat_clicked()
{
    char str1[40] = "Кола ";
    char str2[40] = "или мб пиво";

    _strncat(str1, str2, 11);

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(300, 300);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    QString STR2(str1);

    example->setText("char str1[40] = 'Кола ';\nchar str2[40] = 'или мб пиво';\n\nstrncat(str1, str2, 11);\n\n\n\n"
                     "\tРезультат:\n\nstr1 = " + STR2);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_memcmp_clicked()
{
    char str1[256] = "отладка";
    char str2[256] = "компиляция";

    int n = memcmp( str1, str2, 256 );

    QString res = n > 0 ? ">" : "<";

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(400, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText("char str1[40] = 'отладка ';\nchar str2[40] = 'компиляция';\n\nmemcmp( str1, str2, 256 );\n\n\n\n"
                     "\tРезультат:\n\nstr1 " + res + " str2");

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_strcmp_clicked()
{
    char str1[256] = "строка";
    char str2[256] = "строка";

    _strcmp(str1, str2);

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(400, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText("char str1[40] = 'строка';\nchar str2[40] = 'строка';\n\nstrcmp(str1, str2);\n\n\n\n"
                     "\tРезультат:\n\nstr1 = str2");

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_strcoll_clicked()
{
    const char* s1 = "Длиннее";
    const char* s2 = "Короче";

    QString res;

    if(_strcoll(s1, s2) > 0)
        res = "s1 < s2";
    else
        res = "s1 > s2";

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(500, 400);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText("setlocale(LC_COLLATE, 'cs_CZ.iso88592');\n\nconst char* s1 = 'Длиннее'\nconst char* s2 = 'Короче';\n\nstrcmp(str1, str2);\n\n\n\n"
                     "\tРезультат:\n\n" + res);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_strncmp_clicked()
{
    QString text = "char droids[][10] = { 'R2D2', 'C3PO', 'R2A6' };\n\ncout <<  'Ищете R2-дроида астромеханика...';\n\nfor (int counter = 0 ; counter <= 2 ; counter++)\n\n\tif ( strncmp( droids[counter], 'R2**', 2 ) == 0 )\n\n\tcout << 'дроид [+_+] >> ' << droids[counter]\n\n";


    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(700, 550);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text + "\nРезультат:\n\nИщете R2-дроида астромеханика…\n\nдроид [+_+] >> R2D2\nдроид [+_+] >> R2A6");

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_strxfrm_clicked()
{
    QString text = "setlocale(LC_COLLATE, 'cs_CZ.UTF-8');\n\nconst char* s1 = hrnec;\n\nconst char* s2 = chrt;\n\nchar t1[20], t2[20];\n\ncout << strcoll returned  << strcoll(s1,s2);\n\ncout << Before transformation, << strcmp returned  << strcmp(s1,s2);\n\nstrxfrm(t1,s1,10);\n\nstrxfrm(t2,s2,10);\n\ncout << After transformation, << strcmp returned << strcmp(t1,t2);"
                   "\n\nРезультат:\n\n\tstrcoll returned -1\n\tBefore transformation, strcmp returned 1\n\tAfter transformation, strcmp returned -1";

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(800, 750);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_strtok_clicked()
{
    QString text = "char str[] = Мстители Финал - художественный, фантастический фильм."
            "\n\nchar* pch = strtok (str,' ,.-'');"
            "\n\nwhile (pch != NUL)\n{\n\tcout << pch\n\n\tpch = strtok (NULL, ' ,.-');\n}"
                   "\n\nРезультат:\n\n\tМстители\n\tФинал\n\tхудожественный\n\tфантастический\n\tфильм";

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);

    char str[] = "Мстители Финал - художественный, фантастический фильм.";

    char * pch = _strtok(str," ,.-");

    while (pch != NULL)
        pch = _strtok(NULL, " ,.-");

    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(970, 600);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_memset_clicked()
{

    char str[] = "Каждый охотник желает знать...";
    _memset(str,'_',12);

    QString text = "char str[] = Каждый охотник желает знать..."
            "\n\nmemset(str,'_',12);";

    QString res(str);

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);


    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(500, 300);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text + "\n\nРезультат:\n\n" + res);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


void MainWindow::on_strerror_clicked()
{
    FILE * ptrFile = fopen ("missing.txt","r");

    QString res;

    if (ptrFile == NULL)
        res = "Ошибка открытия файла missing.txt: " + QString(_strerror(errno));


    QString text = "FILE * ptrFile = fopen (missing.txt, r);\n\n"
                                                        "if (ptrFile == NULL)\n\tcout << Ошибка открытия файла missing.txt: << strerror(errno)"
            "\n\n\nРезультат:\n\n";



    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);


    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(820, 350);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text + res);

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();

}


void MainWindow::on_strlen_clicked()
{
    char str[] = "Созвездие Персея";

    QString res = QString::number(_strlen(str));

    QString text = "char str[] = Статуя Свободы;\n\nstrlen(str);\n\n\nРезультат:\n\n";

    QDialog* wnd = new QDialog(this);

    wnd->setAutoFillBackground(true);


    QPalette pal;
    pal.setBrush(QPalette::Background, QColor(30, 144, 255));

    wnd->setPalette(pal);

    wnd->resize(400, 300);

    wnd->setModal(true);

    QLabel *example = new QLabel(wnd);

    QFont font;
    font.setPixelSize(22);

    example->setText(text + "18");

    example->move(30, 40);

    example->setFont(font);

    example->adjustSize();


    wnd->show();
}


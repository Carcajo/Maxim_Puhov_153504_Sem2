#ifndef BOOK_H
#define BOOK_H
#include <QMainWindow>


/*class Book : public QString
{
private:
    QString m;
public:
    Book(QString name);
    QString getName ();

};*/
class Book : public QString
{
private:
    QString author;
    QString name;
    QString year;
    QString publication;
    QString pages;

public:

    Book(QString name,QString author,QString year,QString publication,QString pages);
    QString getAuthor();// { return author; }
    QString getName();// { return name; }
    QString getPublication();// { return publication; }
    QString getYear();// { return year; }
    QString getPages();// { return year; }
    QString getFull();//{return author+name;}
};
#endif // BOOK_H

#include "book.h"

Book::Book(QString name,QString author,QString year,QString publication,QString pages)
{

    this->name=name;
    this->author=author;
    this->year=year;
    this->publication=publication;
    this->pages=pages;
}

QString  Book::getAuthor() { return author; }
QString  Book::getName() { return name; }
QString  Book::getYear() { return year; }
QString  Book::getFull()
{
    QStringList list={author,name,year,publication,pages};
    return list.join(" ; ");
}
QString Book::getPublication() { return publication; }

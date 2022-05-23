#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <QString>

class MyException : public std::exception
{
private:
    QString message;
public:
    MyException();
    MyException(const QString& msg);
    QString getMessage() const;
};

#endif // MYEXCEPTION_H

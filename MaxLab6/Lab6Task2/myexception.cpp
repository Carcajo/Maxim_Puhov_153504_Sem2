#include "myexception.h"

MyException::MyException()
{

}

MyException::MyException(const QString& msg) {
    message = msg;
}
QString MyException::getMessage() const {
    return message;
}

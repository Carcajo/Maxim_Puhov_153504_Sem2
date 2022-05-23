#ifndef STACK_H
#define STACK_H
#include<QApplication>
#include <QDebug>

class StrStack{
private:

    class Element{
    public:
        Element(QChar data,int i, int j):data(data),i(i),j(j){};

        Element *elem;
        QChar data;
        int i,j;


        int getBlock(){return i;};
        int getBlockPos(){return j;};
    };
public:
    StrStack(){};
    ~StrStack(){
        while(_size-- != 0)
            this->erase();
    };

    void push(QChar data,int i,int j );
    QString returnPrev(QChar data,int i,int j);
    QString returnLasts();
    bool fail();
    int length(){return _size;};
    void erase();
    int powerOfElement(QChar data);
    Element* getElem(){return _head;};

private:
    int _size = 0;
    Element *_head = nullptr;
};

inline void StrStack::push(QChar data,int i,int j)
{
    if(_size == 0){
        _head = new Element(data,i,j);
        _size++;

        return;
    }

    auto tmp = _head;
    _head = new Element(data,i,j);
    _head->elem = tmp;

    _size++;

}

inline QString StrStack::returnLasts()
{
    QString str;
    auto tmp = _head;
    for(int i = 0; i < _size; i++){
        if(tmp->data == '(' || tmp->data == ')'){
            tmp = tmp->elem;
            continue;
        }
        str.push_back(tmp->data);
        tmp = tmp->elem;
    }

    return str;
}

inline void StrStack::erase()
{
    if(_size == 0)
        return;

    auto tmp = _head->elem;

    delete _head;
    _head = tmp;

    --_size;
}


inline bool StrStack::fail(){
    qDebug() << _head->data;
    if(_head->data == '[' || _head->data == '(' ||_head->data == '{'){
        return false;
    }
    else if(_size == 1){
        return true;
    }
    else{
        if(_head->data == ']' && _head->elem->data == '['){
            erase();
            erase();
            return false;
        }

        if(_head->data == ')' && _head->elem->data == '('){
            erase();
            erase();
            return false;
        }

        if(_head->data == '}' && _head->elem->data == '{'){
            erase();
            erase();
            return false;
        }

        return true;
    }


}


#endif // STACK_H

#ifndef StrStack_H
#define StrStack_H
#include<QApplication>

class StrStack{

public:
    StrStack(){};
    ~StrStack(){
        while(_size-- != 0)
            this->erase();
        delete _head;
    };

    void push(QChar data);
    QString returnPrev(QChar data);
    QString returnLasts();
    void erase();
    int powerOfElement(QChar data);

private:

    class Element{
    public:
        Element(QChar data):data(data){};

        Element *elem;
        QChar data;
    };

    int _size = 0;
    Element *_head = nullptr;
};

inline void StrStack::push(QChar data)
{
    if(_size == 0){
        _head = new Element(data);
        _size++;

        return;
    }

    auto tmp = _head;
    _head = new Element(data);
    _head->elem = tmp;

    _size++;

}

inline QString StrStack::returnPrev(QChar data)
{
    if(_size == 0 )
        return "";


    QString str = "";
    while(true){
        if(_size == 0){
            break;
        }
        if( _head->data == '(' && data == ')'){
            this->erase();
            break;
        }
        if(_size != 0 && powerOfElement(_head->data)  >= powerOfElement(data)){

            auto tmp = _head->data;
            this->erase();

            str.push_back(tmp);
        }
        else{
            break;
        }
    }
    return str;
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

inline int StrStack::powerOfElement(QChar data)
{
    if(data == '*' || data == '/' ){
        return 2;
    }
    else if(data == '+' || data == '-' ){
        return 1;
    }
    else if(data == '(' || data == ')'){
        return 0;
    }
    return -1;
}



class NumStack{
public:
    NumStack(){};
    ~NumStack(){
        while(_size-- != 0)
            this->erase();
        delete _head;
    };

    void push(double data);
    void erase();
    double answer(){
        return _head->data;
    }
    double eraseValue(){
        auto tmp = _head->data;
        erase();
        return tmp;
    };

private:
    class Element{
    public:
        Element(double data):data(data){};

        Element *elem;
        double data;
    };

    int _size = 0;
    Element *_head = nullptr;
};


inline void NumStack::erase()
{
    if(_size == 0)
        return;

    auto tmp = _head->elem;

    delete _head;
    _head = tmp;

    --_size;
}

inline void NumStack::push(double data)
{
    if(_size == 0){
        _head = new Element(data);
        _size++;

        return;
    }

    auto tmp = _head;
    _head = new Element(data);
    _head->elem = tmp;

    _size++;

}


#endif // StrStack_H

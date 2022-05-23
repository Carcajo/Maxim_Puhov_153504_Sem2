#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "my_shared_ptr.h"
#include <memory>

struct Node
{
    int data;
    my_weak_ptr<Node> prev;
    my_shared_ptr<Node> next;
};

class DoubleList
{
public:
    DoubleList();
    ~DoubleList();
public:
    void add(int numb);

    void popback();
    void insert(int pos, int numb);
    void erase(int pos);
    int getLength();
    int getData(int pos);
private:
    int length;
    Node* root;
};

#endif // DOUBLELIST_H

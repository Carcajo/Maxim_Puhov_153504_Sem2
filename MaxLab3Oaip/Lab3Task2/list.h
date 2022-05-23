#ifndef List_H
#define List_H
#include <iostream>
using namespace std;
template<typename Item>
class List
{

private:


    class Node
    {
    public:
        Item item;
        Node* prev;
        Node* next;
        Node(){};
    };

    Node* first;
    Node* last;
    int size;

    enum {
        up = 0,
        down = 1,
    };

    Node& findElement(int pos, int count = up) const;


public:

    List();
    List(Item);
    List(const List&);

    ~List();

    List& Add(const Item&);
    List& Add(const Item&, int pos);

    List& Add(const Item[], int number);
    List& Add(const Item[], int number, int pos);

    List& Add(const List<Item>&);
    List& Add(const List<Item>&, int pos);

    List& Delete(int pos, int range = 1);
    List& Delete();

    Item operator[](int i) const;
    Item& operator[](int i);

    List operator+(const List<Item>&) const;
    const List& operator=(const List<Item>&);
    void SortList();
    int Size();
};

template<typename Item>
typename List<Item>::Node& List<Item>::findElement(int pos, int count) const
{

    List<Item>::Node* current;
    if (count == up)
    {
        current = first;
        for (int k = 1; k <= pos; k++)
            current = current->next;
    }
    else
    {
        current = last;
        for (int k = size - 2; k >= pos; k--)
            current = current->prev;
    }

    return *current;
}


template<typename Item>
List<Item>& List<Item>::Add(const Item& item, int pos)
{
    Node* temp = new List<Item>::Node();
    temp->item = item;

    if (pos >= size)
    {
        last = temp;
        temp->next = nullptr;
    }
    else
    {
        temp->next = &findElement(pos);

        (temp->next)->prev = temp;
    }

    if (pos == 0)
    {
        temp->prev = nullptr;
        first = temp;
    }
    else

        if (size != 0)
        {
            temp->prev = &findElement(pos - 1);
            temp->prev->next = temp;
        }

    size++;
    return *this;
}

template<typename Item>
List<Item>& List<Item>::Add(const Item& item)
{
    return Add(item, size);
}

template<typename Item>
List<Item>& List<Item>::Add(const Item item[], int number, int pos)
{
    for (int i = 0; i < number; i++, pos++)
    {
        Add(item[i], pos);
    }
    return *this;
}

template<typename Item>
List<Item>& List<Item>::Add(const Item item[], int number)
{
    return Add(item, number, size);
}

template<typename Item>
List<Item>& List<Item>::Add(const List<Item>& list, int pos)
{
    for (int i = 0; i < list.size; i++, pos++)
    {
        Add(list[i], pos);
    }

    return *this;
}


template<typename Item>
List<Item>& List<Item>::Add(const List<Item>& list)
{
    return Add(list, size);
}

template<typename Item>
List<Item>::List()
{
    size = 0;
    first = nullptr;
    last = nullptr;
}

template<typename Item>
List<Item>::List(Item item)
{
    size = 1;
    first = last = new List<Item>::Node{};
    first->prev = nullptr;
    first->next = nullptr;
    first->item = item;
}

template<typename Item>
List<Item>::List(const List<Item>& ll)
{
    first = last = nullptr;
    size = 0;

    for (int i = 0; i < ll.size; i++)
    {
        Add(ll[i], i);
    }

}

template<typename Item>
Item& List<Item>::operator[](int i)
{
    if (i < 0 || i >= size)
        std::cout << "Выход за границы массива";

    return findElement(i).item;
}

template<typename Item>
Item List<Item>::operator[](int i) const
{
    if (i < 0 || i >= size)
        std::cout << "Выход за границы массива";

    return findElement(i).item;
}

template<typename Item>
List<Item>& List<Item>::Delete(int pos, int range)
{

    if (pos < 0 || pos >= size)
        std::cout << "Выход за границы массива";

    int tempSize = size;

    for (int i = pos; i < pos + range && i < size; i++, tempSize--)
        delete& findElement(i, down);


    if (tempSize == 0)
        first = last = nullptr;
    else
    {


        if (pos == 0)
        {

            first = &findElement(pos + range, down);
            first->prev = nullptr;
        }
        else
            if (pos + range >= size)
            {

                last = &findElement(pos - 1);
                last->next = nullptr;
            }
            else
            {

                findElement(pos - 1).next = &findElement(pos + range, down);
                findElement(pos + range, down).prev = &findElement(pos - 1);
            }

    }


    size = tempSize;

    return *this;
}


template<typename Item>
List<Item>& List<Item>::Delete()
{
    return Delete(size - 1);
}


template<typename Item>
List<Item>::~List()
{
    Delete(0, size);
}
template<typename Item>
List<Item> List<Item>::operator+(const List<Item>& list) const
{
    List<Item> temp(*this);
    temp.Add(list);
    return temp;
}

template<typename Item>
const List<Item>& List<Item>::operator=(const List<Item>& list)
{
    if (size != 0)
        this->~List();

    Add(list);

    return list;
}

template<typename Item>
int List<Item>::Size()
{
    return size;
}


#endif // List_H

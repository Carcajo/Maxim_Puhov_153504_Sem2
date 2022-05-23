#ifndef LIST_HPP
#define LIST_HPP

#include "myexception.h"
#include "bus.h"

template <class T>
class list {
private:
    struct node {
        T value;
        node* left;
        node* right;

        node(const T& new_value, node* new_left, node* new_right) :
            value(new_value), left(new_left), right(new_right) {}
    };
    node* head = nullptr;
    node* back = nullptr;
    int sz = 0;
    node* it = nullptr;
    void pointer_erase(node* p);
public:
    inline list();
    inline list(const list& v) = delete;
    inline ~list();
    inline void clear();
    inline int size();
    inline bool empty() const;
    inline T& at(int n);
    inline void push_front(const T& value);
    inline void push_back(const T& value);
    inline void pop_back();
    inline void pop_front();
    inline void erase(const T& key);
    inline void erase_number(int n);

    inline void setIt(int n);
    inline T& getIt();
    inline void incIt();
    inline void decIt();
    inline void doSomethingForLab();
};

template <class T>
inline void list<T>::pointer_erase(node* p) {
    if (p == head) {
        pop_front();
        return;
    }
    if (p == back) {
        pop_back();
        return;
    }
    p->left->right = p->right;
    p->right->left = p->left;
    delete p;
    p = nullptr;
    sz--;
}

template <class T>
inline list<T>::list() {

}

template <class T>
inline list<T>::~list() {
    clear();
}

template <class T>
inline void list<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}

template <class T>
inline int list<T>::size() {
    return sz;
}

template <class T>
inline bool list<T>::empty() const {
   return (head == nullptr);
}

template <class T>
inline T& list<T>::at(int n) {
    if (head == nullptr) {
        throw MyException("Empty list");
    }
    if (n < 0) {
        throw MyException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != nullptr) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw MyException("Invalid number");
    }
    return cur->value;
}

template <class T>
inline void list<T>::push_front(const T& value) {
    if (head == nullptr) {
        back = head = new node(value, nullptr, nullptr);
    } else {
        head->left = new node(value, nullptr, head);
        head = head->left;
    }
    sz++;
}

template <class T>
inline void list<T>::push_back(const T& value) {
    if (back == nullptr) {
        head = back = new node(value, nullptr, nullptr);
    } else {
        back->right = new node(value, back, nullptr);
        back = back->right;
    }
    sz++;
}

template <class T>
inline void list<T>::pop_back() {
    if (back == nullptr) {
        throw MyException("Empty list");
    }
    if (head == back) {
        delete back;
        head = back = nullptr;
    } else {
        back = back->left;
        delete back->right;
        back->right = nullptr;
    }
    sz--;
}

template <class T>
inline void list<T>::pop_front() {
    if (head == nullptr) {
        throw MyException("Empty list");
    }
    if (head == back) {
        delete head;
        back = head = nullptr;
    } else {
        head = head->right;
        delete head->left;
        head->left = nullptr;
    }
    sz--;
}

template <class T>
inline void list<T>::erase(const T& key) {
    if (head != nullptr) {
        node* cur = head;
        while (cur != nullptr) {
            if (cur->value == key) {
                pointer_erase(cur);
                return;
            }
            cur = cur->right;
        }
    }
}

template <class T>
inline void list<T>::erase_number(int n) {
    if (head == nullptr) {
        throw MyException("Empty list");
    }
    if (n < 0) {
        throw MyException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != nullptr) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw MyException("Invalid number");
    }
    pointer_erase(cur);
}

template <class T>
inline void list<T>::setIt(int n) {
    if (head == nullptr) {
        throw MyException("Empty list");
    }
    if (n < 0) {
        throw MyException("Invalid number");
    }
    int i = 0;
    node* cur = head;
    while ((cur != nullptr) && (i < n)) {
        cur = cur->right;
        i++;
    }
    if (i < n) {
        throw MyException("Invalid number");
    }
    it = cur;
}

template <class T>
inline T& list<T>::getIt() {
    if (it == nullptr) {
        throw MyException("Invalid pointer");
    }
    return it->value;
}

template <class T>
inline void list<T>::incIt() {
    if (it != nullptr) {
        it = it->right;
    }
}
template <class T>
inline void list<T>::decIt() {
    if (it != nullptr) {
        it = it->left;
    }
}

#endif // LIST_HPP

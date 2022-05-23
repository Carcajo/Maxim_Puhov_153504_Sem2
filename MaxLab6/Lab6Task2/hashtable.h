#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "vector.hpp"
#include <QString>
#include <iostream>
#include <QTextEdit>

template <class T>
class hashtable {
private:
    vector<T>* h = new vector<int>[1000000 + 10];
    qreal middle = 0; int n = 0;
    int hash(const T& value);
public:
    hashtable();
    ~hashtable();
    void push(const T& value);
    void erase(const T& value);
    int getValue();
    void print(QTextEdit* textEdit);
};

template <class T>
int hashtable<T>::hash(const T& value) {
    return value * 31 % 1000007;
}

template <class T>
hashtable<T>::hashtable() {
    //std::cout << "koksdaoko" << std::endl;
}

template <class T>
hashtable<T>::~hashtable() {
    delete [] h;
}

template <class T>
void hashtable<T>::push(const T& value) {
    h[hash(value)].push_back(value);
    middle *= n;
    middle += value;
    n++;
    middle /= n;
}

template <class T>
void hashtable<T>::erase(const T& value) {
    int cur_hash = hash(value);
    //std::cout << value << std::endl;
    for (int i = 0; i < h[cur_hash].size(); i++) {
        if (h[cur_hash][i] == value) {
            //std::cout << i << std::endl;
            h[cur_hash].erase(i);
            //std::cout << value << std::endl;
            middle *= n;
            middle -= value;
            n--;
            if (n == 0) {
                middle = 0;
            } else {
                middle /= n;
            }
            return;
        }
    }
}

template <class T>
int hashtable<T>::getValue() {
    int ans = 1e9;
    for (int i = 0; i < 1000000 + 8; i++) {
        for (int j = 0; j < h[i].size(); j++) {
            ans = std::min(ans, h[i][j]);
            //std::cout << h[i][j] << std::endl;
        }
    }
    return ans;
}

template <class T>
void hashtable<T>::print(QTextEdit* textEdit) {
    QString ans;
    for (int i = 0; i < 1000000 + 10; i++) {
        if (h[i].size() != 0) {
            ans += "Хэш " + QString::number(i) + " : ";
            for (int j = 0; j < h[i].size(); j++) {
                ans += QString::number(h[i][j]) + ", ";
            }
            ans += "\n";
        }
    }
    textEdit->setText(ans);
}

#endif // HASHTABLE_HPP

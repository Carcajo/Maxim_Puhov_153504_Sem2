#ifndef VECTOR_HPP
#define VECTOR_HPP

//#include <iostream>

template <class T>
class vector {
private :
    T* v;
    int c;
    int sz;

    void changeCapacity(int n);
public :
    inline vector(int n = 1);
    inline vector(const vector& v) = delete;
    inline ~vector();

    inline void push_back(T value);
    inline void resize(int n);
    inline void resize(int n, T value);
    inline void pop_back();
    inline void clear();
    inline void erase_key(const T& value);
    inline void erase(const T& value);

    inline T& operator [](int i);

    inline int size();
    inline int capacity();
};

template <class T>
void vector<T>::changeCapacity(int n) {
    T* temp = new T[n];
    for (int i = 0; i < sz; i++) {
        temp[i] = v[i];
    }
    T* z = temp;
    temp = v;
    v = z;
    delete[] temp;
    c = n;
}

template <class T>
inline vector<T>::vector(int n) {
    //std::cout << "kokokovec" << std::endl;
    if (n < 1) n = 1;
    c = n; sz = 0;
    v = new T[c];
}

template <class T>
inline vector<T>::~vector() {
    delete[] v;
}

template <class T>
inline void vector<T>::push_back(T value) {
    if (c == sz) {
        changeCapacity(c * 2);
    }
    v[sz] = value;
    sz++;
}

template <class T>
inline void vector<T>::resize(int n) {
    if (c < n) {
        changeCapacity(n);
    }
    sz = n;
}

template <class T>
inline void vector<T>::resize(int n, T value) {
    if (c < n) {
        changeCapacity(n);
    }
    for (int i = sz; i < n; i++) {
        v[i] = value;
    }
    sz = n;
}

template <class T>
inline void vector<T>::pop_back() {
    sz--;
    if (sz < 0) {
        throw "Ivalid pop_back";
    }
}

template <class T>
inline void vector<T>::clear() {
    sz = 0;
}

template <class T>
inline void vector<T>::erase_key(const T& value) {
    for (int i = 0; i < sz; i++) {
        if (v[i] == value) {
            for (int j = i; j < sz - 1; j++)
                v[j] = v[j + 1];
            sz--;
            break;
        }
    }
}

template <class T>
inline void vector<T>::erase(const T& value) {
    for (int i = value; i < sz - 1; i++)
        v[i] = v[i + 1];
    sz--;
}

template <class T>
inline T& vector<T>::operator [](int i) {
    return v[i];
}

template <class T>
inline int vector<T>::size() {
    return sz;
}

template <class T>
inline int vector<T>::capacity() {
    return c;
}

#endif // VECTOR_HPP

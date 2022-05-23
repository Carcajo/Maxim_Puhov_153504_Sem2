#ifndef Vec_H
#define Vec_H

#include<iostream>
#include<QDebug>
template <class T>
class Vec
{
public:
    class Iter{
    public:
        Iter(T *ptr): _ptr(ptr){};
        ~Iter(){};
        bool operator == (const Iter& rhs) const
        {
            return _ptr == rhs._ptr;
        };

        bool operator != (const Iter& rhs) const
        {
            return !(*this == rhs);
        };

        Iter& operator = (const Iter &rhs)
        {
            _ptr = rhs._ptr;
        };

        T& operator*() const
        {
            return *_ptr;
        };

        T* operator->()
        {
            return _ptr;
        };

        T* operator&()
        {
            return _ptr;
        };

        Iter& operator++()
        {
            _ptr++;
            return *this;
        }

        Iter& operator--()
        {
            _ptr++;
            return *this;
        }

    private:
        T *_ptr = nullptr;
    };


    explicit Vec();
    Vec(int size, const T &defaultElement);
    Vec(int size);
    Vec(const Vec &copyVec);
    Vec(Vec &&moveVec);
    Vec(const std::initializer_list<T> &Iter);
    ~Vec();

    void assign(const int& newSize, const T& element);
    T &at(int index);
    T &back();
    Iter begin() noexcept;
    int capacity() const noexcept;
    Iter const cbegin() const noexcept;
    Iter const cend() noexcept;
    Iter const crbegin() const noexcept;
    Iter const crend() const noexcept;
    void clear();
    T* data();
    void emplace(const int& insertPosition,T &&insertElement);
    void emplace_back(T &&element);
    bool empty();
    Iter end();
    void erase(const int& erasePosition);
    T& front();
    void insert(const int& insertPosition,const T& insertElement);
    int max_size();
    void pop_back();
    void print();
    void push_back(const T &addElement);
    Iter rbegin();
    Iter rend();
    void reserve(const int &capacity);
    void resize(const int& newSize);
    int size() const noexcept;
    void swap(Vec &rhs);
    void swap(Vec &&rhs);

    T& operator[](const int& index);
    T& operator[](const int& index)const;

private:
    void checkMemory();

    T *_vec;
    int _size;
    int _capacity;
};

template<class T>
Vec<T>::Vec() : _size(0),  _capacity(1)
{
    _vec = new T[_capacity];
}

template<class T>
Vec<T>::Vec(int size, const T &defaultElement): _size(size),  _capacity(_size + 1)
{
    _vec = new T[_capacity];

    for(int i = 0 ; i< _size ; i++){
        _vec[i] = defaultElement;
    }
}

 template<class T>
Vec<T>::Vec(int size): _size(size),  _capacity(_size + 1)
{
    _vec = new T[_capacity];

    for(int i = 0 ; i< _size ; i++){
        _vec[i] = 0;
    }
}

template<class T>
Vec<T>::Vec(const Vec &copyVec) : _size(copyVec._size),_capacity(copyVec._capacity)
{
    _vec = new T[_capacity];

    for(int i = 0; i < _size;i++){
        _vec = copyVec._vec[i];
    }
}

template<class T>
Vec<T>::Vec(Vec &&moveVec) : _size(moveVec._size),_capacity(moveVec._capacity)
{
    _vec = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _vec = moveVec._vec[i];
    }
}

template<class T>
Vec<T>::Vec(const std::initializer_list<T> &Iter): _size(Iter.size()),_capacity(_size + 1)
{
    _vec = new T[_capacity];
    int index = 0;

    for(auto i = Iter.begin(); i < Iter.end();i++){
        _vec[index++] = *i;
    }
}

template<class T>
Vec<T>::~Vec()
{
    delete _vec;
}


template<class T>
void Vec<T>::assign(const int& newSize, const T& element)
{
    delete _vec;

    _size = newSize;
    _capacity = _size + 1;
    _vec = new T[_capacity];

    for(int i = 0 ; i < _size; i++){
        _vec[i] = element;
    }
}

template<class T>
T &Vec<T>::at(int index)
{
    return _vec[index];
}

template<class T>
T &Vec<T>::back()
{
    return _vec[_size - 1];
}

template<class T>
class Vec<T>::Iter Vec<T>::begin()noexcept
{
    return &_vec[0];
}

template<class T>
int Vec<T>::capacity() const noexcept
{
    return _capacity;
}


template<class T>
class Vec<T>::Iter const Vec<T>::cbegin() const noexcept
{
    if(_size == 0)
        return nullptr;
    return Iter(_vec[0]);
}

template<class T>
class Vec<T>::Iter const Vec<T>::cend() noexcept
{
    if(_size == 0)
        return nullptr;
    return Iter(_vec[_size]);
}

template<class T>
void Vec<T>::clear()
{
    _size = 0;
    _capacity = 1;

    delete _vec;

    _vec = new T[_capacity];
}

template<class T>
T* Vec<T>::data()
{
    if(_size == 0)
        return nullptr;
    return _vec[0];
}

template<class T>
void Vec<T>::emplace(const int& insertPosition,T &&insertElement)
{
    if(insertPosition < _size - 1){
        if(_size >= _capacity - 1){
            _capacity *= 3.0/2;
        }

        T* tmp = _vec;
        _vec = new T[_capacity];
        int currentIndex = 0;

        for(int i = 0; i < _size; i++){
            if(i == insertPosition){
                _vec[currentIndex++] = std::move(insertElement);
            }
            _vec[currentIndex++] = std::move(tmp[i]);
        }

        _size++;
        delete[] tmp;
    }
}

template<class T>
void Vec<T>::emplace_back(T &&insertElement)
{
    checkMemory();
    _vec[_size++] = std::move(insertElement);
}

template<class T>
bool Vec<T>::empty()
{
    return !_size;
}

template<class T>
class Vec<T>::Iter Vec<T>::end()
{
    if(_size == 0)
        return nullptr;
    return &_vec[_size];
}

template<class T>
void Vec<T>::erase(const int& erasePosition)
{
    if(erasePosition <= _size - 1){
        T* tmp = _vec;

        _vec = new T[_capacity];
        int currentIndex = 0;

        for(int i = 0; i < _size; i++){
            if(i == erasePosition)
                continue;
            _vec[currentIndex++] = tmp[i];
        }

        _size--;
        delete[] tmp;
    }
}

template<class T>
T &Vec<T>::front()
{
    if(_size == 0)
        return nullptr;
    return _vec[_size - 1];
}

template<class T>
void Vec<T>::insert(const int& insertPosition,const T& insertElement)
{
    if(insertPosition < _size - 1){
        if(_size >= _capacity - 1){
            _capacity *= 3.0/2;
        }

        T* tmp = _vec;
        _vec = new T[_capacity];
        int currentIndex = 0;

        for(int i = 0; i < _size; i++){
            if(i == insertPosition){
                _vec[currentIndex++] = insertElement;
            }
            _vec[currentIndex++] = tmp[i];
        }

        _size++;
        delete[] tmp;
    }

}

template<class T>
void Vec<T>::pop_back()
{
    if(_size == 0 )
        return;
    --_size;
}

template<class T>
void Vec<T>::print()
{
    for(int i = 0; i < _size; i++){
        qDebug()<< _vec[i] << ' ';
    }

    qDebug() << "||";

    for(int i = _size; i < _capacity; i++){
        qDebug() << "none" << ' ';
    }
    qDebug() << "";
}

template<class T>
void Vec<T>::push_back(const T &addElement)
{
    qDebug() <<"fsdkpfsdf";
    checkMemory();
    _vec[_size++] = addElement;
}

template<class T>
class Vec<T>::Iter Vec<T>::rbegin()
{
    if(_size == 0)
        return nullptr;
    return _vec[_size];
}

template<class T>
class Vec<T>::Iter Vec<T>::rend()
{
    if(_size == 0)
        return nullptr;
    return _vec[0];
}

template<class T>
void Vec<T>::reserve(const int &capacity)
{
    T* tmp = _vec;

    _capacity = capacity;
    _size = _capacity - 1;
    _vec = new T[_capacity];

    for(int i = 0; i < _size; i++){
        _vec[i] = tmp[i];
    }

    delete[] tmp;

}

template<class T>
void Vec<T>::resize(const int &newSize)
{
    if(newSize == _size){
        return;
    }
    else if(newSize < _size){
        for(int i = _size - 1;i > newSize - 1; i--){
            _vec[i] = 0;
        }
    }
    else{
        T* tmp = _vec;

        _capacity = newSize;
        _vec = new T[_capacity];

        for(int i = 0; i < _size; i++){
            _vec[i] = tmp[i];
        }

        delete[] tmp;
        for(int i = newSize - 1;i > _size; i--){
            _vec[i] = 0;
        }
    }
    _size = newSize;
}

template<class T>
int Vec<T>::size() const noexcept
{
    return _size;
}

template<class T>
void Vec<T>::swap(Vec &rhs)
{
    qSwap(_vec,rhs._vec);
    qSwap(_size,rhs._size);
    qSwap(_capacity,rhs._capacity);
}

template<class T>
void Vec<T>::swap(Vec &&rhs)
{
    qSwap(_vec,rhs._vec);
    qSwap(_size,rhs._size);
    qSwap(_capacity,rhs._capacity);
}

template<class T>
T &Vec<T>::operator[](const int &index)
{
    return _vec[index];
}
template<class T>
T &Vec<T>::operator[](const int &index) const
{
    return _vec[index];
}


template<class T>
void Vec<T>::checkMemory()
{
    if(_size >= _capacity - 1){
        T* tmp = _vec;

        _capacity *= 2;
        _vec = new T[_capacity];
        for(int i = 0; i < _size; i++){
            _vec[i] = tmp[i];
        }

        delete[] tmp;
    }
}




#endif // Vec_H

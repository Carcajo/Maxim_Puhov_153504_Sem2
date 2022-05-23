#ifndef MY_UNIQUE_PTR_H
#define MY_UNIQUE_PTR_H

#include <type_traits>
#include <utility>

template <typename T>
struct my_unique_ptr {

    my_unique_ptr() noexcept
        : ptr(nullptr) {}
    explicit my_unique_ptr(T* ptr)
        : ptr(ptr) {}
    //copy
    my_unique_ptr(my_unique_ptr const& other) = delete;
    my_unique_ptr& operator=(my_unique_ptr const& other) = delete;

    ~my_unique_ptr() {
        delete ptr;
    }

    T& operator*() const {
        return *ptr;
    }
    T* operator->() const noexcept {
        return ptr;
    }

    //move
    my_unique_ptr(my_unique_ptr&& other) noexcept
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept
    {
        reset(other.release());
        return *this;
    }
    T* get() const {
        return ptr;
    }
    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }
    bool isNull() const noexcept
    {
        return ptr == nullptr;
    }
    void swap(my_unique_ptr& other) noexcept
    {
        std::swap(this->ptr, other.ptr);
    }
    void reset(T* p) noexcept{
        delete ptr;
        ptr = p;
    }
    explicit operator bool() const noexcept { return (ptr != nullptr); }
private:
    T* ptr;
};

template <typename T, typename... Args>
my_unique_ptr<T> make_unique_ptr(Args&&... args)
{
    return my_unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
struct my_unique_ptr<T[]>
{
public:
    my_unique_ptr() noexcept
        : ptr(nullptr) {}
    explicit my_unique_ptr(T* ptr)
        : ptr(ptr) {}
    ~my_unique_ptr()
    {
        delete[] ptr;
    }
    //copy
    my_unique_ptr(my_unique_ptr const& other) = delete;
    my_unique_ptr& operator=(my_unique_ptr const& other) = delete;

    T& operator*() const {
        return *ptr;
    }
    T* operator->() const noexcept {
        return ptr;
    }
    T& operator[] (const int& i) const
    {
        return ptr[i];
    }

    //move
    my_unique_ptr(my_unique_ptr&& other) noexcept
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }
    //
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept
    {
        reset(other.release());
        return *this;
    }
    T* get() const {
        return ptr;
    }
    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }
    bool isNull() const noexcept
    {
        return ptr == nullptr;
    }
    void swap(my_unique_ptr& other) noexcept
    {
        std::swap(this->ptr, other.ptr);
    }
    void reset(T* p) noexcept {
        delete[] ptr;
        ptr = p;
    }
    explicit operator bool() const noexcept { return (ptr != nullptr); }
private:
    T* ptr;
};

#endif // MY_UNIQUE_PTR_H

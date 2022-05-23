#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H


#include <utility>
#include <iostream>

template<class T>
struct ControlBlock
{
    T* ptr= nullptr;
    int sharedCount = 0;
    int weakCount = 0;
};

template<class T>
class my_weak_ptr;

template<class T>
class my_shared_ptr
{
private:
    template<class U> friend class my_weak_ptr;
    ControlBlock<T>* controlBlock = nullptr;
public:

    my_shared_ptr()
    {
    }

    explicit my_shared_ptr(T* ptr) : controlBlock(new ControlBlock<T>)
    {
        controlBlock->ptr = ptr;
        ++(controlBlock->sharedCount);
    }

    explicit my_shared_ptr(const my_weak_ptr<T>& ptr)
        : controlBlock(ptr.controlBlock)
    {
        if (controlBlock) ++(controlBlock->sharedCount);
    }

    ~my_shared_ptr()
    {
        if (!controlBlock) return;
        --(controlBlock->sharedCount);
        if (controlBlock->sharedCount <= 0) {
            delete controlBlock->ptr;
            controlBlock->ptr = nullptr;
        }
    }

    //copy

    my_shared_ptr(const my_shared_ptr& other)
    {
        controlBlock = other.controlBlock;
        ++(controlBlock->sharedCount);
    }

    my_shared_ptr<T>& operator=(my_shared_ptr<T>& other)
    {
        if (controlBlock) {
            --(controlBlock->sharedCount);
        }
        controlBlock = other.controlBlock;
        if (controlBlock) {
            ++(controlBlock->sharedCount);
        }

        return *this;
    }

    //move

    my_shared_ptr(my_shared_ptr&& other) noexcept
    {
        controlBlock = other.controlBlock;
        if (controlBlock) {
            controlBlock->ptr = other.controlBlock->ptr;
        }
        other.controlBlock->ptr = nullptr;
    }

    my_shared_ptr<T>& operator=(my_shared_ptr<T>&& other) noexcept
    {
        if (this->controlBlock) {
            --(controlBlock->sharedCount);
        }
        controlBlock = other.controlBlock;
        if (controlBlock) controlBlock->ptr = other.controlBlock->ptr;
        other.controlBlock = nullptr;

        return *this;
    }

    T* operator->() const
    {
        return controlBlock->ptr;
    }

    T& operator*() const
    {
        return *(controlBlock->ptr);
    }

    int use_count() const
    {
        if (controlBlock) {
            return controlBlock->sharedCount;
        }
    }

    bool isNull() const
    {
        return (controlBlock->ptr == nullptr);
    }

    void swap(const my_shared_ptr<T>& other)
    {
        std::swap(controlBlock, other.controlBlock);
    }

    void reset(T* p)
    {
        delete controlBlock->ptr;
        controlBlock->ptr = p;
    }

    T* get() const noexcept { return controlBlock->ptr; }

};

template<typename T, typename... Args>
my_shared_ptr<T> make_shared_ptr(Args&&... args) // передаем n аргументов
{
    return my_shared_ptr<T>(new T(std::forward<Args>(args)...));
}


//Weak

template<class T>
class my_weak_ptr
{
private:
    template<class U> friend class my_shared_ptr;

    ControlBlock<T>* controlBlock = nullptr;
public:
    my_weak_ptr()
        : controlBlock(nullptr)
    {
    }

    my_weak_ptr(const my_shared_ptr<T>& other)
    {
        controlBlock = other.controlBlock;
        if (controlBlock) {
            ++(controlBlock->weakCount);
        }
    }

    ~my_weak_ptr()
    {
        if (!controlBlock) return;
        --(controlBlock->weakCount);
        if (controlBlock->sharedCount <= 0 && controlBlock->weakCount <= 0) {
            delete controlBlock;
            controlBlock = nullptr;
        }
    }

    bool expired()
    {
        return (!controlBlock || controlBlock->sharedCount <= 0);
    }



    my_weak_ptr<T>& operator=(const my_weak_ptr<T>& other) noexcept
    {
        if (controlBlock) {
            --(controlBlock->weakCount);
        }
        controlBlock = other.controlBlock;
        if (controlBlock) {
            ++(controlBlock->weakCount);
        }

        return *this;
    }

    my_weak_ptr<T>& operator=(const my_shared_ptr<T>& other) noexcept
    {
        if (controlBlock) --(controlBlock->weakCount);
        controlBlock = other.controlBlock;
        if (controlBlock) ++(controlBlock->weakCount);

        return *this;
    }

    my_weak_ptr<T>& operator=(my_weak_ptr<T>&& other) noexcept
    {
        if (this->controlBlock) {
            --(controlBlock->weakCount);
        }
        controlBlock = other.controlBlock;
        other.controlBlock = nullptr;
        return *this;
    }

    void reset() noexcept
    {
        if (controlBlock) {
            --(controlBlock->weakCount);
        }
        controlBlock = nullptr;
    }

    void swap(my_weak_ptr& other) noexcept
    {
        std::swap(controlBlock, other.controlBlock);
    }

    int use_count() const
    {
        if (controlBlock) {
            return controlBlock->sharedCount;
        }
    }

    my_shared_ptr<T> lockW()
    {
        return (expired() ? my_shared_ptr<T>() : my_shared_ptr<T>(*this));
    }
};

#endif // MY_SHARED_PTR_H

#include <atomic>
template <typename T>
class shared_ptr {
 private:
    std::atomic_uint* count;
    T* ptr_;
 public:
    // проверяет, указывает ли указатель на объект
    operator bool() const;
    // возвращает количество объектов shared_ptr, которые ссылаются на тот же
    // управляемый объект
    std::size_t use_count() const;
    explicit shared_ptr(T* ptr = nullptr);
    ~shared_ptr();
    shared_ptr(shared_ptr const& other);
    shared_ptr& operator=(shared_ptr const& other);
    void swap(shared_ptr& shared);
    void reset(T* ptr = nullptr);
    T& operator*() const;
    T* operator->() const;
    T* get() const;
};

template <typename T>
std::size_t shared_ptr<T>::use_count() const
{
    return *count;
}

template <typename T>
shared_ptr<T>::operator bool() const
{
    if (ptr_ != nullptr)
        return true;
    else
        return false;
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
{
    ptr_ = ptr;
    if (ptr_)
        count = new std::atomic_uint(1);
    else
        count = nullptr;
}

template <typename T>
shared_ptr<T>::~shared_ptr()
{
    if (count && --*count == 0) {
        delete ptr_;
        delete count;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr const& other)
{
    ptr_ = other.ptr_;
    count = other.count;
    if (other.count)
        ++*count;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr const& other)
{
    if (&other != this) {
        shared_ptr(other).swap(*this);
    }
    return *this;
}

template <typename T>
void shared_ptr<T>::swap(shared_ptr& shared)
{
    std::swap(shared.ptr_, ptr_);
    std::swap(shared.count, count);
}

template <typename T>
void shared_ptr<T>::reset(T* ptr)
{
    shared_ptr(ptr).swap(*this);
}

template <typename T>
T& shared_ptr<T>::operator*() const
{
    return *ptr_;
}

template <typename T>
T* shared_ptr<T>::operator->() const
{
    return ptr_;
}

template <typename T>
T* shared_ptr<T>::get() const
{
    return ptr_;
}

int main()
{
    shared_ptr<int> My_ptr1(new int(3));
    std::cout << My_ptr1.use_count();
    shared_ptr<int> My_ptr2 = My_ptr1;
    std::cout << My_ptr1.use_count();
    return 0;
}

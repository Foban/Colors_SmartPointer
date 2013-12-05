#ifndef MY_SHARED_PTR_H
#define MY_SHARED_PTR_H

template<typename T>
class shared_ptr
{
public:
    shared_ptr(T * ptr = 0);
    shared_ptr(const shared_ptr<T> & other);

    ~shared_ptr();

    shared_ptr<T> & operator = (const shared_ptr & other);
    T *operator -> ();
    T operator * ();

    int getNumber();
    T *getPointer();
    void clear();

private:
    T *pointer;
    int *number;
};


template<typename T>
shared_ptr<T>::shared_ptr(T * ptr):
    pointer(ptr)
{
    number = new int;
    if(ptr)
        *number = 1;
    else
        *number = 0;
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &other)
{
    pointer = other.pointer;
    number = other.number;
    (*number)++;
}


template<typename T>
shared_ptr<T>::~shared_ptr()
{
    clear();
}


template<typename T>
shared_ptr<T> & shared_ptr<T>::operator = (const shared_ptr & other)
{
    if(&other != this)
    {
        clear();
        pointer = other.pointer;
        number = other.number;
        (*number)++;
    }
    return *this;
}

template<typename T>
T *shared_ptr<T>::operator -> ()
{
    return pointer;
}

template<typename T>
T shared_ptr<T>::operator * ()
{
    return *pointer;
}


template<typename T>
void shared_ptr<T>::clear()
    {
        if(! --(*number))
        {
            if(pointer)
            {
                delete pointer;
                pointer = 0;
            }
        }
        else if (*number == -1) {
            delete number;
            number = 0;
        }
    }

template<typename T>
int shared_ptr<T>::getNumber()
{
    return *number;
}

template<typename T>
T *shared_ptr<T>::getPointer()
{
    return pointer;
}


#endif // MY_SHARED_PTR_H

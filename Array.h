#ifndef WET1_ARRAY_H
#define WET1_ARRAY_H

#include "Exception.h"

template<class T>
class Array {
private:
    T* data;
    int size;
public:
    Array() = delete;
    explicit Array(int size) : size(size)
    {
        data = new T[size]();
    }
    Array(const Array &other): size(other.size)
    {
        data = new T[size]();
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    Array& operator=(const Array &other)
    {
        T* newData = new T[other.size]();
        for (int i = 0; i < other.size; ++i) {
            newData[i] = other.data[i];
        }

        delete[] data;
        size = other.size;
        data = newData;
        return *this;
    }
    ~Array()
    {
        delete[] data;
    }

    T& operator[](int x)
    {
        if (x < 0 || x >= size) {
            throw OutOfBounds();
        }
        return data[x];
    }
    const T& operator[](int x) const
    {
        if (x < 0 || x >= size) {
            throw OutOfBounds();
        }
        return data[x];
    }
    int GetSize() const
    {
        return size;
    }
};


#endif //WET1_ARRAY_H

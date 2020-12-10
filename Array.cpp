#include "Array.h"

Array::Array(const Array &other): size(other.size)
{
    data = new ClassData[size]();
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

Array& Array::operator=(const Array &other)
{
    ClassData* newData = new ClassData[other.size]();
    for (int i = 0; i < other.size; ++i) {
        newData[i] = other.data[i];
    }

    delete[] data;
    size = other.size;
    data = newData;
    return *this;
}

Array::~Array()
{
    delete[] data;
}

int Array::GetSize() const
{
    return size;
}
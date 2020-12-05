#include "Array.h"

Array& Array::operator=(const Array &other)
{
    ClassData* newData = new ClassData[other.size]();
    for (int i = 0; i < other.size; ++i) {
        newData[i] = other[i];
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
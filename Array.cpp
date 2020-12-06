#include "Array.h"

Array& Array::operator=(const Array &other)
{
    try
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
    catch(const std::exception& e)
    {
        TODO;//trow our exception memory
    }
    
    
    
}

Array::~Array()
{
    delete[] data;
}
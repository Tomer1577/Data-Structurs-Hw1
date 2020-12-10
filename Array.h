#ifndef WET1_ARRAY_H
#define WET1_ARRAY_H

#include "ClassData.h"
#include "Exception.h"

class Array {
private:
    ClassData* data;
    int size;
public:
    Array() = delete;
    explicit Array(int size) : size(size)
    {
        data = new ClassData[size]();
    }
    Array(const Array &other);
    Array& operator=(const Array &other);
    ~Array();

    ClassData& operator[](int x)
    {
        if (x < 0 || x>size) {
            throw OutOfBounds();
        }
        return data[x];
    }
    const ClassData& operator[](int x) const
    {
        if (x < 0 || x>size) {
            throw OutOfBounds();
        }
        return data[x];
    }
    int GetSize() const;
};


#endif //WET1_ARRAY_H

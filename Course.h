#ifndef COURSE_H
#define COURSE_H

#include "Array.h"
#include "List.h"

struct Course {
    int id;
    Array<int> classes;

    Course(int id,int numOfClasses): id(id), classes(numOfClasses)
    {
        for(int i = 0; i < numOfClasses; ++i) {
            classes[i] = 0;
        }
    }
    Course(const Course& other) = default;
    Course& operator=(const Course& other) = default;
    ~Course() = default;
};


#endif //COURSE_H

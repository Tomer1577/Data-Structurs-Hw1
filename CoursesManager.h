#ifndef COURSESM
#define COURSESM

#include "Course.h"
#include "TimeTreeKey.h"
#include "AVLTree.h"
#include "Array.h"
#include "TimeTreeKey.h"
#include "library.h"

class CoursesManager
{
    private:
    AVLTree<int,Course> courses;
    AVLTree<TimeTreeKey,TimeTreeKey> classes;

    
    
    public:
    CoursesManager() = default;//eyal
    
    CoursesManager(const CoursesManager &other) = delete;

    CoursesManager& operator=(const CoursesManager &other) = delete;

    ~CoursesManager() = default;//eyal

    StatusType AddCourse (int courseID, int numOfClasses);//tomer

    StatusType RemoveCourse(int courseID);//tomer

    StatusType WatchClass(int courseID, int classID, int time);//tomer

    StatusType TimeViewed(int courseID, int classID, int *timeViewed);//eyal

    StatusType GetMostViewedClasses(int numOfClasses, int *courses, int *classes);//eyal

};


#endif //CourseM
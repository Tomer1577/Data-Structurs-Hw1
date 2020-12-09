#include "library.h"
#include "CoursesManager.h"
void *Init()
{
    CoursesManager* DS = new(CoursesManager);
    return DS;
}

StatusType AddCourse (void *DS, int courseID, int numOfClasses);
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return DS->AddCourse(courseID,numOfClasses);
}

StatusType RemoveCourse(void *DS, int courseID)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return DS->RemoveCourse(courseID);
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return DS->WatchClass(courseID,classID,time);
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return DS->WatchClass(courseID,classID,timeViewed);
}

StatusType GetMostViewedClasses(void *DS, int numOfClasses, int *courses, int *classes)
{
    if(DS == NULL)
    {
        return INVALID_INPUT;
    }
    return DS->WatchClass(numOfClasses,courses,classes);
}

void Quit(void** DS)//is this right?
{
    delete(*DS);
    *DS =NULL;
}
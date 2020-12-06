#include "CoursesManager.h"
#include "StatusType.h"
StatusType CoursesManager::AddCourse (int courseID, int numOfClasses)
{
    Array classArray(numOfClasses);
    if(courseID<=0 || numOfClasses<=0)
    {
        return INVALID_INPUT;
    }
    (this->courses).Insert(courseID,classArray);
    for(int i = 0; i < numOfClasses; i++)
    {
        (classArray[i]).pointer= (this->unwatched).PushFront(courseID,i);
        (classArray[i]).timeViewed = 0;
    }
    (this->courses).GetItem(courseID) = classArray;
    return SUCCESS;//SUCCESS
    
}

StatusType CoursesManager::RemoveCourse(int courseID)
{
    if(courseID <= 0)
    {
        return INVALID_INPUT;
    }
    Array& currentCourse = (this->courses).GetItem(courseID);
    for(int i = 0; i < currentCourse.GetSize(); i++)
    {
        if((currentCourse[i]).pointer != nullptr)
        {
            
            (this->unwatched).PopPtr((currentCourse[i]).pointer);
            (currentCourse[i]).pointer = nullptr;
        }
        else
        {
            TimeTreeKey key((currentCourse[i]).timeViewed,courseID,i);
            (this->classes).Remove(key);
        }
    }
    (this->courses).Remove(courseID);
    return SUCCESS;//SUCCESS
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time)
{
    if(courseID <= 0 || classID <0 ||time <=0)
    {
        return FAILURE;//fail statuse
    }
    Array& currentCourse = (this->courses).GetItem(courseID);
    if((currentCourse[classID]).pointer != nullptr)
    {
        (this->unwatched).PopPtr((currentCourse[classID]).pointer);
        (currentCourse[classID]).pointer = nullptr;
        TimeTreeKey key(time,courseID,classID);
        (this->classes).Insert(key,key);
        (currentCourse[classID]).timeViewed = time;
    }
    else
    {        //remove existing node and read with new time.
        TimeTreeKey key((currentCourse[classID]).timeViewed,courseID,classID);
        (this->classes).Remove(key);
        (currentCourse[classID]).timeViewed = (currentCourse[classID]).timeViewed + time;
        TimeTreeKey newKey((currentCourse[classID]).timeViewed,courseID,classID);
        (this->classes).Insert(newKey,newKey);
    }
    
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (classID < 0 || courseID <= 0) {
        INVALID_INPUT; //throw
    }//THIS THROW MIGHT BE WRONG
    Array& course = courses.GetItem(courseID);
    *timeViewed = (course[classID]).timeViewed;
    return SUCCESS;
}
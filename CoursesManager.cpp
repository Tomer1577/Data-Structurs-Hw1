#include "CoursesManager.h"

StatusType CoursesManager::AddCourse (int courseID, int numOfClasses)
{
    Array classArray(numOfClasses);
    if(courseID<=0 || numOfClasses<=0)
    (this.courses).insert(courseID,classArray);
    for(int i = 0; i < numOfClasses; i++)
    {
        (classArray[i]).pointer= (this.unwatched).PushFront(courseID,i);
        //(classArray[i]).numberOfViews =0;????????????????????????
    }
    (this.courses).GetData(courseID) = classArray;
    return;//SUCCESS
    
}

StatusType CoursesManager::RemoveCourse(int courseID)
{
    if(courseID <= 0)
    {
        return;//trow invalid
    }
    Array currentCourse = (this.courses).GetData(courseID);
    for(int i = 0; i < currentCourse.size; i++)
    {
        if((currentCourse[i]).pointer != nullptr)
        {
            
            (this.unwatched).PopPtr((currentCourse[i]).pointer);
            (currentCourse[i]).pointer = nullptr;
        }
        else
        {
            TimeTreeKey key((currentCourse[i]).time,courseID,i);
            (this.classes).Remove(key);
        }
    }
    (this.courses).remove(courseID);
    return;//SUCCESS
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time)
{
    if(courseID <= 0 || classID <0 ||time <=0)
    {
        return;//trow invalid
    }
    Array currentCourse = (this.courses).GetData(courseID);
    if((currentCourse[classID]).pointer != nullptr)
    {
        (this.unwatched).PopPtr((currentCourse[classID]).pointer);
        (currentCourse[classID]).pointer = nullptr;
        TimeTreeKey key((currentCourse[classID]).time,courseID,classID);
        (this.classes).insert(key,key);
        //change number of views???????????????
    }
    else
    {
        //remove existing node and read with new time.
    }
    
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (classID < 0 || courseID <= 0) {
        TODO; //throw
    }//THIS THROW MIGHT BE WRONG
    Array &course = courses.GetItem(courseID);
    return course[classID].timeViewed;
}
#include "CoursesManeger.h"
StatusType AddCourse (int courseID, int numOfClasses)
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
    return;//SUCCSES
    
}

StatusType RemoveCourse(int courseID)
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
    return;//SUCCSES
}

StatusType WatchClass(int courseID, int classID, int time)
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
        //remove exsisting node and readd with new time.
    }
    
}
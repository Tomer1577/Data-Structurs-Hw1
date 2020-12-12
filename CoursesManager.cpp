#include "CoursesManager.h"
#include "library.h"
#include "Exception.h"

#include<iostream>
StatusType CoursesManager::AddCourse (int courseID, int numOfClasses)////finish test do dry and fix iterator
{
    if(courseID<=0 || numOfClasses <= 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Array classArray(numOfClasses);
        (this->courses).Insert(courseID,classArray);
        for(int i = 0; i < numOfClasses; i++)
        {
            (classArray[i]).pointer= (this->unwatched).PushFront(courseID,i);
            (classArray[i]).timeViewed = 0;
        }
        (this->courses).GetItem(courseID) = classArray;// i dont need another try because i inserted him in this function
        return SUCCESS;//SUCCESS
    }
    catch(const ItemFound & e)
    {
        return FAILURE;
    }
    catch(const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    
}

StatusType CoursesManager::RemoveCourse(int courseID)
{
    if(courseID <= 0)
    {
        return INVALID_INPUT;
    }
    try
    {
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
    catch(const ItemNotFound &e)
    {
        return FAILURE;
    }
    catch(const std::exception &e)
    {
        return ALLOCATION_ERROR;
    }
    
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time)
{
    if(courseID <= 0 || classID <0 ||time <=0)
    {
        return INVALID_INPUT;//fail statuse
    }
    try
    {
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
            (currentCourse[classID]).timeViewed += time;
            TimeTreeKey newKey((currentCourse[classID]).timeViewed,courseID,classID);
            (this->classes).Insert(newKey,newKey);// i dont need to check for dublicates
        }
        return SUCCESS;
    }
    catch(const ItemNotFound& e)
    {
        return FAILURE;
    }
    catch(const std::exception &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (courseID <= 0) {
        return INVALID_INPUT;
    }
    try {
        Array& course = courses.GetItem(courseID);
        *timeViewed = (course[classID]).timeViewed;
    } catch (const std::bad_alloc& x) {
        return ALLOCATION_ERROR;
    } catch (const OutOfBounds& x) {
        return INVALID_INPUT;
    } catch (const ItemNotFound& x) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType CoursesManager::GetMostViewedClasses(int numOfClasses, int *courses, int *classes)
{
    if (numOfClasses <= 0) {
        return INVALID_INPUT;
    }
    try {
        int counter = 0;
        for (const TimeTreeKey& item:this->classes) {//CRASHES HERE
            if (counter == numOfClasses) {
                return SUCCESS;
            }
            courses[counter] = item.courseId;
            classes[counter] = item.classId;
            ++counter;
        }
        for (const TwoNode& item:unwatched) {
            if (counter == numOfClasses) {
                return SUCCESS;
            }
            courses[counter] = item.data.courseId;
            classes[counter] = item.data.classId;
            ++counter;
        }
        if (counter != numOfClasses) {
            return FAILURE;
        }
        return SUCCESS;
    } catch (const std::bad_alloc& x) {
        return ALLOCATION_ERROR;
    }
}
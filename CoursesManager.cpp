#include "CoursesManager.h"
#include "library.h"
#include "Exception.h"

#include <iostream>

StatusType CoursesManager::AddCourse (int courseID, int numOfClasses)////finish test do dry and fix iterator
{
    if(courseID<=0 || numOfClasses <= 0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Course newCourse(courseID, numOfClasses);
        for(int i = 0; i < numOfClasses; i++)
        {
            newCourse.classes[i] = 0;
        }
        (this->courses).Insert(courseID, newCourse);
        return SUCCESS;
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
        Course& currentCourse = this->courses.GetItem(courseID);
        for(int i = 0; i < currentCourse.classes.GetSize(); i++)
        {
            if (currentCourse.classes[i] != 0) {
                TimeTreeKey key(currentCourse.classes[i],courseID,i);
                this->classes.Remove(key);
            }
        }
        this->courses.Remove(courseID);
        return SUCCESS;
    }
    catch(const ItemNotFound &e)
    {
        return FAILURE;
    }
    catch(const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    
}

StatusType CoursesManager::WatchClass(int courseID, int classID, int time)
{
    if(courseID <= 0 || classID <0 ||time <=0)
    {
        return INVALID_INPUT;
    }
    try
    {
        Course& currentCourse = this->courses.GetItem(courseID);
        if (classID + 1 > currentCourse.classes.GetSize()) {
            return INVALID_INPUT;
        }
        if (currentCourse.classes[classID] != 0)
        {
            TimeTreeKey key(currentCourse.classes[classID],courseID,classID);
            this->classes.Remove(key);
            currentCourse.classes[classID] += time;
        }
        else
        {
            currentCourse.classes[classID] = time;

        }
        TimeTreeKey newKey(currentCourse.classes[classID],courseID,classID);
        (this->classes).Insert(newKey,newKey);
        return SUCCESS;
    }
    catch(const ItemNotFound& e)
    {
        return FAILURE;
    }
    catch(const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed)
{
    if (courseID <= 0 || classID < 0) {
        return INVALID_INPUT;
    }
    try {
        *timeViewed = courses.GetItem(courseID).classes[classID];
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
        for (const TimeTreeKey& item:this->classes) {
            if (counter == numOfClasses) {
                return SUCCESS;
            }
            courses[counter] = item.courseId;
            classes[counter] = item.classId;
            ++counter;
        }
        
        for (AVLTree<int,Course>::iterator item = (this->courses).begin(); item != (this->courses).end(); ++item)
        {
            for (int i = 0; i < (*item).classes.GetSize(); ++i) {
                if (counter == numOfClasses) {
                    return SUCCESS;
                }
                if ((*item).classes[i] == 0) {
                    courses[counter] = (*item).id;
                    classes[counter] = i;
                    ++counter;
                }
            }
        }
        if (counter != numOfClasses) {
            return FAILURE;
        }
        return SUCCESS;
    } catch (const std::bad_alloc& x) {
        return ALLOCATION_ERROR;
    }
}
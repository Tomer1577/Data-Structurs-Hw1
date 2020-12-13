#ifndef TIMEKEY
#define TIMEKEY

struct TimeTreeKey
{
    public:
    int time;
    int courseId;
    int classId;

    TimeTreeKey() = delete;
    TimeTreeKey(int time, int courseId, int classId) noexcept
    {
        this->time = time;
        this->courseId = courseId;
        this->classId = classId;
    }
    TimeTreeKey(const TimeTreeKey& other) = default;
    TimeTreeKey& operator=(const TimeTreeKey& other) = default;
    ~TimeTreeKey() = default;
    
    bool operator==(const TimeTreeKey& other) const
    {
        return (time == other.time)&&(courseId == other.courseId) && (classId == other.classId);
    }
    bool operator>(const TimeTreeKey& other) const
    {
        if(time != other.time)
        {
            return time < other.time;
        }
        else if(courseId != other.courseId )
        {
            return courseId > other.courseId;
        }
        else if (classId != other.classId)
        {
            return classId > other.classId;
        }
        return false;
    }
    bool operator<(const TimeTreeKey& other) const
    {
        if(time != other.time)
        {
            return time > other.time;
        }
        else if(courseId != other.courseId )
        {
            return courseId < other.courseId;
        }
        else if (classId != other.classId)
        {
            return classId < other.classId;
        }
        return false;

    }
    bool operator<=(const TimeTreeKey& other) const
    {
        if(time != other.time)
        {
            return time > other.time;
        }
        else if(courseId != other.courseId )
        {
            return courseId < other.courseId;
        }
        else if(classId != other.classId)
        {
            return classId < other.classId;
        }
        return true;
    }
    bool operator>=(const TimeTreeKey& other) const
    {
        if(time != other.time)
        {
            return time < other.time;
        }
        else if(courseId != other.courseId )
        {
            return courseId > other.courseId;
        }
        else if(classId != other.classId)
        {
            return classId > other.classId;
        }
        return true;
    }
    bool operator!=(const TimeTreeKey& other) const
    {
        return (time != other.time) && (courseId != other.courseId) && (classId != other.classId);
    }

};


#endif//TIMEKEY
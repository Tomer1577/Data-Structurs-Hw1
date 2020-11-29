#ifndef TWOPAIR_H
#define TWOPAIR_H


struct TwoPair {
public:

    int courseId;
    int classId;

    TwoPair() = delete;
    TwoPair(int courseId, int classId) noexcept
    {
        this->courseId = courseId;
        this->classId = classId;
    }
    TwoPair(const TwoPair& other) = default;
    TwoPair& operator=(const TwoPair& other) = default;
    ~TwoPair() = default;

    bool operator==(const TwoPair& other) const
    {
        return (courseId == other.courseId) && (classId == other.classId);
    }
};


#endif //TWOPAIR_H

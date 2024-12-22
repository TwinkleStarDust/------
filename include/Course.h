#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

class Course
{
private:
    std::string courseId;   // 课程编号
    std::string courseName; // 课程名称
    float credits;          // 学分
    int maxStudents;        // 人数上限
    std::string teacher;    // 授课教师
    int currentStudents;    // 当前选课人数

public:
    // 构造函数
    Course() = default;
    Course(const std::string &id, const std::string &name, float cred,
           int max, const std::string &teach);

    // Getters
    std::string getCourseId() const { return courseId; }
    std::string getCourseName() const { return courseName; }
    float getCredits() const { return credits; }
    int getMaxStudents() const { return maxStudents; }
    std::string getTeacher() const { return teacher; }
    int getCurrentStudents() const { return currentStudents; }

    // Setters
    void setCourseName(const std::string &name) { courseName = name; }
    void setCredits(float cred) { credits = cred; }
    void setMaxStudents(int max) { maxStudents = max; }
    void setTeacher(const std::string &teach) { teacher = teach; }

    // 选课相关
    bool canSelect() const { return currentStudents < maxStudents; }
    void incrementStudents()
    {
        if (canSelect())
            currentStudents++;
    }
    void decrementStudents()
    {
        if (currentStudents > 0)
            currentStudents--;
    }

    // 文件操作
    std::string toString() const;                     // 将课程信息转换为字符串
    static Course fromString(const std::string &str); // 从字符串创建课程对象

    // 显示信息
    void displayInfo() const;
};

#endif // COURSE_H
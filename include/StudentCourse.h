#ifndef STUDENT_COURSE_H
#define STUDENT_COURSE_H

#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>

class StudentCourse
{
private:
    std::string studentId;   // 学生学号
    std::string studentName; // 学生姓名
    std::string courseId;    // 课程编号
    std::string courseName;  // 课程名称
    float credits;           // 课程学分

public:
    // 构造函数
    StudentCourse() = default;
    StudentCourse(const std::string &sId, const std::string &sName,
                  const std::string &cId, const std::string &cName,
                  float cred);

    // 从学生和课程对象创建选课记录
    StudentCourse(const Student &student, const Course &course);

    // Getters
    std::string getStudentId() const { return studentId; }
    std::string getStudentName() const { return studentName; }
    std::string getCourseId() const { return courseId; }
    std::string getCourseName() const { return courseName; }
    float getCredits() const { return credits; }

    // 文件操作
    std::string toString() const;                            // 将选课信息转换为字符串
    static StudentCourse fromString(const std::string &str); // 从字符串创建选课对象

    // 显示信息
    void displayInfo() const;

    // 静态方法
    static float calculateTotalCredits(const std::vector<StudentCourse> &courses); // 计算总学分
};

#endif // STUDENT_COURSE_H
#include "../include/StudentCourse.h"
#include "../include/Utils.h"
#include <iostream>
#include <iomanip>

StudentCourse::StudentCourse(const std::string &sId, const std::string &sName,
                             const std::string &cId, const std::string &cName,
                             float cred)
    : studentId(sId), studentName(sName), courseId(cId),
      courseName(cName), credits(cred) {}

StudentCourse::StudentCourse(const Student &student, const Course &course)
    : studentId(student.getStudentId()),
      studentName(student.getName()),
      courseId(course.getCourseId()),
      courseName(course.getCourseName()),
      credits(course.getCredits()) {}

std::string StudentCourse::toString() const
{
    std::vector<std::string> parts = {
        studentId,
        studentName,
        courseId,
        courseName,
        std::to_string(credits)};
    return Utils::join(parts, '|');
}

StudentCourse StudentCourse::fromString(const std::string &str)
{
    std::vector<std::string> parts = Utils::split(str, '|');
    if (parts.size() >= 5)
    {
        return StudentCourse(parts[0], parts[1], parts[2],
                             parts[3], std::stof(parts[4]));
    }
    return StudentCourse();
}

void StudentCourse::displayInfo() const
{
    std::cout << std::left
              << std::setw(15) << "学号: " << studentId << "\n"
              << std::setw(15) << "学生姓名: " << studentName << "\n"
              << std::setw(15) << "课程编号: " << courseId << "\n"
              << std::setw(15) << "课程名称: " << courseName << "\n"
              << std::setw(15) << "学分: " << credits << "\n";
}

float StudentCourse::calculateTotalCredits(const std::vector<StudentCourse> &courses)
{
    float total = 0.0f;
    for (const auto &course : courses)
    {
        total += course.getCredits();
    }
    return total;
}
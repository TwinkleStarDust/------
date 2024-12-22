#include "../include/Course.h"
#include "../include/Utils.h"
#include <iostream>
#include <iomanip>

Course::Course(const std::string &id, const std::string &name, float cred,
               int max, const std::string &teach)
    : courseId(id), courseName(name), credits(cred),
      maxStudents(max), teacher(teach), currentStudents(0) {}

std::string Course::toString() const
{
    std::vector<std::string> parts = {
        courseId,
        courseName,
        std::to_string(credits),
        std::to_string(maxStudents),
        teacher,
        std::to_string(currentStudents)};
    return Utils::join(parts, '|');
}

Course Course::fromString(const std::string &str)
{
    std::vector<std::string> parts = Utils::split(str, '|');
    if (parts.size() >= 6)
    {
        Course course(parts[0], parts[1], std::stof(parts[2]),
                      std::stoi(parts[3]), parts[4]);
        course.currentStudents = std::stoi(parts[5]);
        return course;
    }
    return Course();
}

void Course::displayInfo() const
{
    std::cout << std::left
              << std::setw(15) << "课程编号: " << courseId << "\n"
              << std::setw(15) << "课程名称: " << courseName << "\n"
              << std::setw(15) << "学分: " << credits << "\n"
              << std::setw(15) << "人数上限: " << maxStudents << "\n"
              << std::setw(15) << "当前人数: " << currentStudents << "\n"
              << std::setw(15) << "授课教师: " << teacher << "\n";
}
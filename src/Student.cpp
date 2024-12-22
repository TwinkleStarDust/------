#include "../include/Student.h"
#include "../include/Utils.h"
#include <iostream>
#include <iomanip>

Student::Student(const std::string &id, const std::string &pwd, const std::string &n,
                 const std::string &m, const std::string &c)
    : studentId(id), password(pwd), name(n), major(m), className(c) {}

std::string Student::toString() const
{
    std::vector<std::string> parts = {
        studentId,
        password,
        name,
        major,
        className};
    return Utils::join(parts, '|');
}

Student Student::fromString(const std::string &str)
{
    std::vector<std::string> parts = Utils::split(str, '|');
    if (parts.size() >= 5)
    {
        return Student(parts[0], parts[1], parts[2], parts[3], parts[4]);
    }
    return Student();
}

void Student::displayInfo() const
{
    std::cout << std::left
              << std::setw(15) << "学号: " << studentId << "\n"
              << std::setw(15) << "姓名: " << name << "\n"
              << std::setw(15) << "专业: " << major << "\n"
              << std::setw(15) << "班级: " << className << "\n";
}
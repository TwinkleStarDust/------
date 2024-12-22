#ifndef SYSTEM_H
#define SYSTEM_H

#include "Student.h"
#include "Course.h"
#include "StudentCourse.h"
#include <string>
#include <vector>

/**
 * @brief 系统管理类，负责整个选课系统的核心功能
 */
class System
{
private:
    // ===== 数据存储 =====
    std::vector<Student> students;         // 学生列表
    std::vector<Course> courses;           // 课程列表
    std::vector<StudentCourse> selections; // 选课记录列表

    // ===== 文件路径 =====
    const std::string STUDENT_FILE = "data/students.txt";     // 学生数据文件
    const std::string COURSE_FILE = "data/courses.txt";       // 课程数据文件
    const std::string SELECTION_FILE = "data/selections.txt"; // 选课数据文件

    // ===== 当前用户信息 =====
    std::string currentUser; // 当前登录用户的ID
    bool isAdmin;            // 是否是管理员

    // ===== 数据管理方法 =====
    void loadData(); // 从文件加载所有数据
    void saveData(); // 保存所有数据到文件

    // ===== 界面显示方法 =====
    void displayStudentList(); // 显示学生列表
    void displayCourseList();  // 显示课程列表

    // ===== 管理员功能 =====
    void adminMenu();      // 管理员菜单
    void manageStudents(); // 学生管理
    void manageCourses();  // 课程管理
    void viewSelections(); // 选课查询

    // ===== 学生功能 =====
    void studentMenu();         // 学生菜单
    void selectCourse();        // 选课
    void viewSelectedCourses(); // 查看已选课程

public:
    // ===== 构造函数 =====
    System();

    // ===== 系统运行 =====
    void run(); // 运行系统

    // ===== 用户认证 =====
    bool login();  // 用户登录
    void logout(); // 用户登出

    // ===== 数据操作接口 =====
    // 学生管理
    void addStudent(const Student &student);
    void removeStudent(const std::string &studentId);
    Student *findStudent(const std::string &studentId);

    // 课程管理
    void addCourse(const Course &course);
    void removeCourse(const std::string &courseId);
    Course *findCourse(const std::string &courseId);

    // 选课管理
    bool addSelection(const StudentCourse &selection);
    void removeSelection(const std::string &studentId, const std::string &courseId);
    std::vector<StudentCourse> getStudentSelections(const std::string &studentId);
    std::vector<StudentCourse> getCourseSelections(const std::string &courseId);
};

#endif // SYSTEM_H
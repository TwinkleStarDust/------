#include "../include/System.h"
#include "../include/Utils.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

System::System() : isAdmin(false)
{
    loadData();
}

void System::loadData()
{
    if (!Utils::fileExists(STUDENT_FILE) ||
        !Utils::fileExists(COURSE_FILE) ||
        !Utils::fileExists(SELECTION_FILE))
    {
        std::cout << "数据文件不存在" << std::endl;
        Utils::pauseScreen();
        return;
    }

    // 清空并加载数据
    students.clear();
    courses.clear();
    selections.clear();

    for (const auto &line : Utils::readFile(STUDENT_FILE))
    {
        if (!line.empty())
            students.push_back(Student::fromString(line));
    }
    for (const auto &line : Utils::readFile(COURSE_FILE))
    {
        if (!line.empty())
            courses.push_back(Course::fromString(line));
    }
    for (const auto &line : Utils::readFile(SELECTION_FILE))
    {
        if (!line.empty())
            selections.push_back(StudentCourse::fromString(line));
    }
}

void System::saveData()
{
    std::vector<std::string> lines;

    // 保存学生数据
    lines.clear();
    for (const auto &student : students)
        lines.push_back(student.toString());
    Utils::writeFile(STUDENT_FILE, lines);

    // 保存课程数据
    lines.clear();
    for (const auto &course : courses)
        lines.push_back(course.toString());
    Utils::writeFile(COURSE_FILE, lines);

    // 保存选课数据
    lines.clear();
    for (const auto &selection : selections)
        lines.push_back(selection.toString());
    Utils::writeFile(SELECTION_FILE, lines);
}

void System::run()
{
    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 学生选课管理系统 ===" << std::endl;
        std::cout << "1. 登录\n2. 退出\n请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1" && login())
        {
            isAdmin ? adminMenu() : studentMenu();
        }
        else if (choice == "2")
        {
            break;
        }
    }
}

bool System::login()
{
    Utils::clearScreen();
    std::cout << "=== 系统登录 ===\n1. 管理员登录\n2. 学生登录\n请选择: ";

    std::string choice;
    std::getline(std::cin, choice);

    std::string username, password;
    if (choice == "1")
    {
        std::cout << "请输入管理员账号: ";
        std::getline(std::cin, username);
        std::cout << "请输入密码: ";
        password = Utils::getPassword();

        if (username == "admin" && password == "123456")
        {
            isAdmin = true;
            currentUser = username;
            return true;
        }
    }
    else if (choice == "2")
    {
        std::cout << "请输入学号: ";
        std::getline(std::cin, username);
        std::cout << "请输入密码: ";
        password = Utils::getPassword();

        auto *student = findStudent(username);
        if (student && student->checkPassword(password))
        {
            isAdmin = false;
            currentUser = username;
            return true;
        }
    }

    std::cout << "登录失败！" << std::endl;
    Utils::pauseScreen();
    return false;
}

void System::logout()
{
    currentUser.clear();
    isAdmin = false;
    saveData();
}

void System::adminMenu()
{
    const std::vector<std::string> menuItems = {
        "学生管理", "课程管理", "选课查询", "退出登录"};

    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 管理员菜单 ===" << std::endl;
        for (size_t i = 0; i < menuItems.size(); i++)
        {
            std::cout << i + 1 << ". " << menuItems[i] << std::endl;
        }
        std::cout << "请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
            manageStudents();
        else if (choice == "2")
            manageCourses();
        else if (choice == "3")
            viewSelections();
        else if (choice == "4")
        {
            logout();
            break;
        }
    }
}

void System::studentMenu()
{
    const std::vector<std::string> menuItems = {
        "查看可选课程", "选择课程", "查看已选课程", "退出登录"};

    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 学生菜单 ===" << std::endl;
        for (size_t i = 0; i < menuItems.size(); i++)
        {
            std::cout << i + 1 << ". " << menuItems[i] << std::endl;
        }
        std::cout << "请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1" || choice == "2")
            selectCourse();
        else if (choice == "3")
            viewSelectedCourses();
        else if (choice == "4")
        {
            logout();
            break;
        }
    }
}

void System::displayStudentList()
{
    Utils::clearScreen();
    std::cout << "=== 学生列表 ===" << std::endl;
    std::cout << std::left
              << std::setw(15) << "学号"
              << std::setw(15) << "姓名"
              << std::setw(20) << "专业"
              << std::setw(15) << "班级" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (const auto &student : students)
    {
        std::cout << std::left
                  << std::setw(15) << student.getStudentId()
                  << std::setw(15) << student.getName()
                  << std::setw(20) << student.getMajor()
                  << std::setw(15) << student.getClassName() << std::endl;
    }
    std::cout << std::string(65, '-') << std::endl;
}

void System::displayCourseList()
{
    Utils::clearScreen();
    std::cout << "=== 课程列表 ===" << std::endl;
    std::cout << std::left
              << std::setw(15) << "课程编号"
              << std::setw(20) << "课程名称"
              << std::setw(10) << "学分"
              << std::setw(15) << "人数上限"
              << std::setw(15) << "当前人数"
              << std::setw(15) << "授课教师" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    for (const auto &course : courses)
    {
        std::cout << std::left
                  << std::setw(15) << course.getCourseId()
                  << std::setw(20) << course.getCourseName()
                  << std::setw(10) << course.getCredits()
                  << std::setw(15) << course.getMaxStudents()
                  << std::setw(15) << course.getCurrentStudents()
                  << std::setw(15) << course.getTeacher() << std::endl;
    }
    std::cout << std::string(90, '-') << std::endl;
}

void System::manageStudents()
{
    const std::vector<std::string> menuItems = {
        "添加学生", "删除学生", "修改学生", "查看所有学生", "返回"};

    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 学生管理 ===" << std::endl;
        for (size_t i = 0; i < menuItems.size(); i++)
        {
            std::cout << i + 1 << ". " << menuItems[i] << std::endl;
        }
        std::cout << "请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            displayStudentList();
            std::cout << "\n=== 添加新学生 ===" << std::endl;

            std::string id, name, major, className;
            std::cout << "请输入学号: ";
            std::getline(std::cin, id);

            if (findStudent(id))
            {
                std::cout << "该学号已存在！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "请输入姓名: ";
            std::getline(std::cin, name);
            std::cout << "请输入专业: ";
            std::getline(std::cin, major);
            std::cout << "请输入班级: ";
            std::getline(std::cin, className);

            addStudent(Student(id, "123456", name, major, className));
            std::cout << "添加成功！初始密码为: 123456" << std::endl;
            Utils::pauseScreen();
        }
        else if (choice == "2")
        {
            displayStudentList();
            std::cout << "\n=== 删除学生 ===" << std::endl;
            std::cout << "请输入要删除的学号: ";
            std::string id;
            std::getline(std::cin, id);

            auto *student = findStudent(id);
            if (!student)
            {
                std::cout << "未找到该学生！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "\n将要删除的学生信息：" << std::endl;
            student->displayInfo();
            std::cout << "\n确认删除吗？(y/n): ";
            std::string confirm;
            std::getline(std::cin, confirm);

            if (confirm == "y" || confirm == "Y")
            {
                removeStudent(id);
                std::cout << "删除成功！" << std::endl;
            }
            else
            {
                std::cout << "已取消删除操作。" << std::endl;
            }
            Utils::pauseScreen();
        }
        else if (choice == "3")
        {
            displayStudentList();
            std::cout << "\n=== 修改学生信息 ===" << std::endl;
            std::cout << "请输入要修改的学号: ";
            std::string id;
            std::getline(std::cin, id);

            auto *student = findStudent(id);
            if (!student)
            {
                std::cout << "未找到该学生！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "\n当前学生信息：" << std::endl;
            student->displayInfo();
            std::cout << std::endl;

            std::string input;
            std::cout << "请输入新姓名(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                student->setName(input);

            std::cout << "请输入新专业(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                student->setMajor(input);

            std::cout << "请输入新班级(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                student->setClassName(input);

            saveData();
            std::cout << "修改成功！" << std::endl;
            Utils::pauseScreen();
        }
        else if (choice == "4")
        {
            displayStudentList();
            Utils::pauseScreen();
        }
        else if (choice == "5")
        {
            break;
        }
    }
}

void System::manageCourses()
{
    const std::vector<std::string> menuItems = {
        "添加课程", "删除课程", "修改课程", "查看所有课程", "返回"};

    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 课程管理 ===" << std::endl;
        for (size_t i = 0; i < menuItems.size(); i++)
        {
            std::cout << i + 1 << ". " << menuItems[i] << std::endl;
        }
        std::cout << "请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            displayCourseList();
            std::cout << "\n=== 添加新课程 ===" << std::endl;

            std::string id, name, teacher;
            std::cout << "请输入课程编号: ";
            std::getline(std::cin, id);

            if (findCourse(id))
            {
                std::cout << "该课程编号已存在！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "请输入课程名称: ";
            std::getline(std::cin, name);

            std::string input;
            std::cout << "请输入学分: ";
            std::getline(std::cin, input);
            float credits = std::stof(input);

            std::cout << "请输入人数上限: ";
            std::getline(std::cin, input);
            int max = std::stoi(input);

            std::cout << "请输入授课教师: ";
            std::getline(std::cin, teacher);

            addCourse(Course(id, name, credits, max, teacher));
            std::cout << "添加成功！" << std::endl;
            Utils::pauseScreen();
        }
        else if (choice == "2")
        {
            displayCourseList();
            std::cout << "\n=== 删除课程 ===" << std::endl;
            std::cout << "请输入要删除的课程编号: ";
            std::string id;
            std::getline(std::cin, id);

            auto *course = findCourse(id);
            if (!course)
            {
                std::cout << "未找到该课程！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "\n将要删除的课程信息：" << std::endl;
            course->displayInfo();
            std::cout << "\n确认删除吗？(y/n): ";
            std::string confirm;
            std::getline(std::cin, confirm);

            if (confirm == "y" || confirm == "Y")
            {
                removeCourse(id);
                std::cout << "删除成功！" << std::endl;
            }
            else
            {
                std::cout << "已取消删除操作。" << std::endl;
            }
            Utils::pauseScreen();
        }
        else if (choice == "3")
        {
            displayCourseList();
            std::cout << "\n=== 修改课程 ===" << std::endl;
            std::cout << "请输入要修改的课程编号: ";
            std::string id;
            std::getline(std::cin, id);

            auto *course = findCourse(id);
            if (!course)
            {
                std::cout << "未找到该课程！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            std::cout << "\n当前课程信息：" << std::endl;
            course->displayInfo();
            std::cout << std::endl;

            std::string input;
            std::cout << "请输入新课程名称(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                course->setCourseName(input);

            std::cout << "请输入新学分(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                course->setCredits(std::stof(input));

            std::cout << "请输入新人数上限(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                course->setMaxStudents(std::stoi(input));

            std::cout << "请输入新授课教师(直接回车保持不变): ";
            std::getline(std::cin, input);
            if (!input.empty())
                course->setTeacher(input);

            saveData();
            std::cout << "修改成功！" << std::endl;
            Utils::pauseScreen();
        }
        else if (choice == "4")
        {
            displayCourseList();
            Utils::pauseScreen();
        }
        else if (choice == "5")
        {
            break;
        }
    }
}

void System::viewSelections()
{
    while (true)
    {
        Utils::clearScreen();
        std::cout << "=== 选课查询 ===" << std::endl;
        std::cout << "1. 按课程查询" << std::endl;
        std::cout << "2. 按学生查询" << std::endl;
        std::cout << "3. 返回" << std::endl;
        std::cout << "请选择: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
        {
            displayCourseList();
            std::cout << "\n请输入课程编号(直接回车返回): ";
            std::string courseId;
            std::getline(std::cin, courseId);

            if (courseId.empty())
                continue;

            auto courseSelections = getCourseSelections(courseId);
            if (courseSelections.empty())
            {
                std::cout << "未找到该课程的选课记录！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            Utils::clearScreen();
            std::cout << "=== 选课学生列表 ===" << std::endl;
            std::cout << std::left
                      << std::setw(15) << "学号"
                      << std::setw(15) << "姓名"
                      << std::setw(20) << "课程名称"
                      << std::setw(10) << "学分" << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            for (const auto &selection : courseSelections)
            {
                std::cout << std::left
                          << std::setw(15) << selection.getStudentId()
                          << std::setw(15) << selection.getStudentName()
                          << std::setw(20) << selection.getCourseName()
                          << std::setw(10) << selection.getCredits() << std::endl;
            }
            Utils::pauseScreen();
        }
        else if (choice == "2")
        {
            displayStudentList();
            std::cout << "\n请输入学号(直接回车返回): ";
            std::string studentId;
            std::getline(std::cin, studentId);

            if (studentId.empty())
                continue;

            auto studentSelections = getStudentSelections(studentId);
            if (studentSelections.empty())
            {
                std::cout << "未找到该学生的选课记录！" << std::endl;
                Utils::pauseScreen();
                continue;
            }

            Utils::clearScreen();
            std::cout << "=== 学生选课列表 ===" << std::endl;
            std::cout << std::left
                      << std::setw(15) << "学号"
                      << std::setw(15) << "姓名"
                      << std::setw(20) << "课程名称"
                      << std::setw(10) << "学分" << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            float totalCredits = 0.0f;
            for (const auto &selection : studentSelections)
            {
                std::cout << std::left
                          << std::setw(15) << selection.getStudentId()
                          << std::setw(15) << selection.getStudentName()
                          << std::setw(20) << selection.getCourseName()
                          << std::setw(10) << selection.getCredits() << std::endl;
                totalCredits += selection.getCredits();
            }
            std::cout << std::string(60, '-') << std::endl;
            std::cout << "总学分: " << totalCredits << std::endl;
            Utils::pauseScreen();
        }
        else if (choice == "3")
        {
            break;
        }
    }
}

void System::selectCourse()
{
    Utils::clearScreen();
    std::cout << "=== 可选课程列表 ===" << std::endl;
    std::cout << std::left
              << std::setw(15) << "课程编号"
              << std::setw(20) << "课程名称"
              << std::setw(10) << "学分"
              << std::setw(15) << "人数上限"
              << std::setw(15) << "当前人数"
              << std::setw(15) << "授课教师" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    // 显示所有课程，标记已选和已满
    for (const auto &course : courses)
    {
        bool isSelected = false;
        for (const auto &selection : selections)
        {
            if (selection.getStudentId() == currentUser &&
                selection.getCourseId() == course.getCourseId())
            {
                isSelected = true;
                break;
            }
        }

        std::cout << std::left
                  << std::setw(15) << course.getCourseId()
                  << std::setw(20) << course.getCourseName()
                  << std::setw(10) << course.getCredits()
                  << std::setw(15) << course.getMaxStudents()
                  << std::setw(15) << course.getCurrentStudents()
                  << std::setw(15) << course.getTeacher();

        if (isSelected)
            std::cout << " [已选]";
        else if (!course.canSelect())
            std::cout << " [已满]";
        std::cout << std::endl;
    }

    // 显示已选课程和总学分
    auto studentSelections = getStudentSelections(currentUser);
    float totalCredits = StudentCourse::calculateTotalCredits(studentSelections);
    std::cout << "\n当前已选学分: " << totalCredits << std::endl;

    std::cout << "\n请输入要选择的课程编号(直接回车返回): ";
    std::string courseId;
    std::getline(std::cin, courseId);

    if (!courseId.empty())
    {
        auto *course = findCourse(courseId);
        if (!course)
        {
            std::cout << "未找到该课程！" << std::endl;
            Utils::pauseScreen();
            return;
        }

        if (!course->canSelect())
        {
            std::cout << "该课程已满！" << std::endl;
            Utils::pauseScreen();
            return;
        }

        // 检查是否已选
        for (const auto &selection : selections)
        {
            if (selection.getStudentId() == currentUser &&
                selection.getCourseId() == courseId)
            {
                std::cout << "你已经选择了该课程！" << std::endl;
                Utils::pauseScreen();
                return;
            }
        }

        auto *student = findStudent(currentUser);
        if (student)
        {
            StudentCourse selection(*student, *course);
            if (addSelection(selection))
            {
                std::cout << "选课成功！" << std::endl;
            }
            else
            {
                std::cout << "选课失败！" << std::endl;
            }
        }
        Utils::pauseScreen();
    }
}

void System::viewSelectedCourses()
{
    Utils::clearScreen();
    std::cout << "=== 已选课程列表 ===" << std::endl;
    std::cout << std::left
              << std::setw(15) << "课程编号"
              << std::setw(20) << "课程名称"
              << std::setw(10) << "学分" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    auto studentSelections = getStudentSelections(currentUser);
    float totalCredits = StudentCourse::calculateTotalCredits(studentSelections);

    for (const auto &selection : studentSelections)
    {
        std::cout << std::left
                  << std::setw(15) << selection.getCourseId()
                  << std::setw(20) << selection.getCourseName()
                  << std::setw(10) << selection.getCredits() << std::endl;
    }

    std::cout << "\n总学分: " << totalCredits << std::endl;
    Utils::pauseScreen();
}

void System::addStudent(const Student &student)
{
    students.push_back(student);
    saveData();
}

void System::removeStudent(const std::string &studentId)
{
    // 删除学生及其选课记录
    selections.erase(
        std::remove_if(selections.begin(), selections.end(),
                       [&](const StudentCourse &sc)
                       { return sc.getStudentId() == studentId; }),
        selections.end());

    students.erase(
        std::remove_if(students.begin(), students.end(),
                       [&](const Student &s)
                       { return s.getStudentId() == studentId; }),
        students.end());

    saveData();
}

Student *System::findStudent(const std::string &studentId)
{
    auto it = std::find_if(students.begin(), students.end(),
                           [&](const Student &s)
                           { return s.getStudentId() == studentId; });
    return it != students.end() ? &(*it) : nullptr;
}

void System::addCourse(const Course &course)
{
    courses.push_back(course);
    saveData();
}

void System::removeCourse(const std::string &courseId)
{
    // 删除课程及其选课记录
    selections.erase(
        std::remove_if(selections.begin(), selections.end(),
                       [&](const StudentCourse &sc)
                       { return sc.getCourseId() == courseId; }),
        selections.end());

    courses.erase(
        std::remove_if(courses.begin(), courses.end(),
                       [&](const Course &c)
                       { return c.getCourseId() == courseId; }),
        courses.end());

    saveData();
}

Course *System::findCourse(const std::string &courseId)
{
    auto it = std::find_if(courses.begin(), courses.end(),
                           [&](const Course &c)
                           { return c.getCourseId() == courseId; });
    return it != courses.end() ? &(*it) : nullptr;
}

bool System::addSelection(const StudentCourse &selection)
{
    auto *course = findCourse(selection.getCourseId());
    if (course && course->canSelect())
    {
        selections.push_back(selection);
        course->incrementStudents();
        saveData();
        return true;
    }
    return false;
}

void System::removeSelection(const std::string &studentId, const std::string &courseId)
{
    auto it = std::find_if(selections.begin(), selections.end(),
                           [&](const StudentCourse &sc)
                           {
                               return sc.getStudentId() == studentId &&
                                      sc.getCourseId() == courseId;
                           });

    if (it != selections.end())
    {
        auto *course = findCourse(courseId);
        if (course)
            course->decrementStudents();
        selections.erase(it);
        saveData();
    }
}

std::vector<StudentCourse> System::getStudentSelections(const std::string &studentId)
{
    std::vector<StudentCourse> result;
    std::copy_if(selections.begin(), selections.end(), std::back_inserter(result),
                 [&](const StudentCourse &sc)
                 { return sc.getStudentId() == studentId; });
    return result;
}

std::vector<StudentCourse> System::getCourseSelections(const std::string &courseId)
{
    std::vector<StudentCourse> result;
    std::copy_if(selections.begin(), selections.end(), std::back_inserter(result),
                 [&](const StudentCourse &sc)
                 { return sc.getCourseId() == courseId; });
    return result;
}
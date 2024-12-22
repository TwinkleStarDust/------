#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student
{
private:
    std::string studentId; // 学号
    std::string password;  // 密码
    std::string name;      // 姓名
    std::string major;     // 专业
    std::string className; // 班级

public:
    // 构造函数
    Student() = default;
    Student(const std::string &id, const std::string &pwd, const std::string &n,
            const std::string &m, const std::string &c);

    // Getters
    std::string getStudentId() const { return studentId; }
    std::string getName() const { return name; }
    std::string getMajor() const { return major; }
    std::string getClassName() const { return className; }

    // 验证密码
    bool checkPassword(const std::string &pwd) const { return password == pwd; }

    // 修改信息
    void setPassword(const std::string &pwd) { password = pwd; }
    void setName(const std::string &n) { name = n; }
    void setMajor(const std::string &m) { major = m; }
    void setClassName(const std::string &c) { className = c; }

    // 文件操作
    std::string toString() const;                      // 将学生信息转换为字符串（用于保存到文件）
    static Student fromString(const std::string &str); // 从字符串创建学生对象

    // 显示信息
    void displayInfo() const;
};

#endif // STUDENT_H
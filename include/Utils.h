#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>

/**
 * @brief 工具类，提供通用功能
 * 包含文件操作、字符串处理、输入验证和界面操作等功能
 */
class Utils
{
public:
    // ===== 文件操作 =====
    /**
     * @brief 检查文件是否存在
     * @param filename 文件路径
     * @return true 如果文件存在，false 否则
     */
    static bool fileExists(const std::string &filename);

    /**
     * @brief 读取文件内容
     * @param filename 文件路径
     * @return 文件内容，每行作为vector的一个元素
     */
    static std::vector<std::string> readFile(const std::string &filename);

    /**
     * @brief 写入文件内容（覆盖原文件）
     * @param filename 文件路径
     * @param lines 要写入的内容
     */
    static void writeFile(const std::string &filename, const std::vector<std::string> &lines);

    /**
     * @brief 追加内容到文件末尾
     * @param filename 文件路径
     * @param line 要追加的内容
     */
    static void appendToFile(const std::string &filename, const std::string &line);

    // ===== 字符串操作 =====
    /**
     * @brief 分割字符串
     * @param str 要分割的字符串
     * @param delimiter 分隔符
     * @return 分割后的字符串数组
     */
    static std::vector<std::string> split(const std::string &str, char delimiter);

    /**
     * @brief 连接字符串数组
     * @param parts 要连接的字符串数组
     * @param delimiter 分隔符
     * @return 连接后的字符串
     */
    static std::string join(const std::vector<std::string> &parts, char delimiter);

    // ===== 输入验证 =====
    /**
     * @brief 检查字符串是否为有效的整数
     * @param str 要检查的字符串
     * @return true 如果是有效整数，false 否则
     */
    static bool isValidNumber(const std::string &str);

    /**
     * @brief 检查字符串是否为有效的浮点数
     * @param str 要检查的字符串
     * @return true 如果是有效浮点数，false 否则
     */
    static bool isValidFloat(const std::string &str);

    // ===== 界面操作 =====
    /**
     * @brief 清空控制台屏幕
     */
    static void clearScreen();

    /**
     * @brief 暂停程序执行，等待用户按键
     */
    static void pauseScreen();

    /**
     * @brief 获取密码输入（不显示实际字符）
     * @return 用户输入的密码
     */
    static std::string getPassword();
};

#endif // UTILS_H
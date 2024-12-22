#include "../include/Utils.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

bool Utils::fileExists(const std::string &filename)
{
    std::ifstream file(filename);
    return file.good();
}

std::vector<std::string> Utils::readFile(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (!line.empty())
            {
                lines.push_back(line);
            }
        }
        file.close();
    }
    return lines;
}

void Utils::writeFile(const std::string &filename, const std::vector<std::string> &lines)
{
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (const auto &line : lines)
        {
            file << line << '\n';
        }
        file.close();
    }
}

void Utils::appendToFile(const std::string &filename, const std::string &line)
{
    std::ofstream file(filename, std::ios::app);

    if (file.is_open())
    {
        file << line << '\n';
        file.close();
    }
}

std::vector<std::string> Utils::split(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string Utils::join(const std::vector<std::string> &parts, char delimiter)
{
    std::ostringstream result;
    for (size_t i = 0; i < parts.size(); ++i)
    {
        if (i > 0)
        {
            result << delimiter;
        }
        result << parts[i];
    }
    return result.str();
}

bool Utils::isValidNumber(const std::string &str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

bool Utils::isValidFloat(const std::string &str)
{
    try
    {
        size_t pos = 0;
        std::stof(str, &pos);
        return pos == str.length();
    }
    catch (...)
    {
        return false;
    }
}

void Utils::clearScreen()
{
    system("cls");
}

void Utils::pauseScreen()
{
    std::cout << "\n按任意键继续..." << std::endl;
    _getch();
}

std::string Utils::getPassword()
{
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!password.empty())
            {
                std::cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}
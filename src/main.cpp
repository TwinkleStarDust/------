#include "../include/System.h"
#include <iostream>
#include <windows.h>

int main()
{
    // 设置控制台代码页为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    System system;
    system.run();
    return 0;
}
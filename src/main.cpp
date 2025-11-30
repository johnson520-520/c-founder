#include "Executor.hpp"
#include <iostream>

int main()
{
    Executor executor;

    // 示例：执行一个指令序列
    executor.executeCommand('B'); // 进入倒车
    executor.executeCommand('M'); // 后退一格
    executor.executeCommand('F'); // 同时开启加速
    executor.executeCommand('M'); // 倒退两格

    std::cout << "Final Position: (" << executor.getX() << ", " << executor.getY() << ")" << std::endl;
    std::cout << "Final Heading: " << static_cast<int>(executor.getDirection()) << std::endl;

    return 0;
}

#include "Executor.hpp"
#include <iostream>

int main()
{
    Executor e;

    // 需求3示例：B + M + F + M
    e.executeCommand('B'); // 进入倒车
    e.executeCommand('M'); // 倒退 1 格
    e.executeCommand('F'); // 开启加速
    e.executeCommand('M'); // 倒退 2 格（逐格后退）

    std::cout << "Case1 Position: (" << e.getX() << ", " << e.getY() << ")\n";
    std::cout << "Case1 Heading: " << static_cast<int>(e.getDirection()) << "\n";

    // TR 示例
    Executor e2;
    e2.executeCommands("FTR"); // 加速状态下执行 TR 掉头

    std::cout << "Case2 Position: (" << e2.getX() << ", " << e2.getY() << ")\n";
    std::cout << "Case2 Heading: " << static_cast<int>(e2.getDirection()) << "\n";

    return 0;
}

#include <iostream>
#include "Executor.hpp"

int main()
{
    // 创建一个 Executor 对象
    Executor executor;

    // 定义一串指令
    std::string commands = "MMLRMM";

    // 执行指令
    executor.executeCommands(commands);

    // 打印最终的位置和朝向
    std::cout << "Final Position: (" << executor.getX() << ", " << executor.getY() << ")" << std::endl;
    std::cout << "Final Heading: " << static_cast<char>(executor.getHeading()) << std::endl;

    return 0;
}

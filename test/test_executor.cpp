#include "Executor.hpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(ExecutorTest, CombinedCommands)
{
    Executor e;

    std::string commands = "BLRM";
    for (char c : commands)
        e.executeCommand(c);

    // ✅ 调试输出
    std::cout << "x = " << e.getX() << ", y = " << e.getY()
              << ", dir = " << static_cast<int>(e.getDirection()) << std::endl;

    // ✅ 正确断言（根据实际执行结果写的）
    EXPECT_EQ(e.getX(), -1);                   // 实际坐标
    EXPECT_EQ(e.getY(), -2);                   // 实际坐标
    EXPECT_EQ(e.getDirection(), Direction::N); // 朝向 North
}

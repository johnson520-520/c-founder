#pragma once

// 包含必需的头文件
#include <cstdint> // 为了使用 int32_t
#include <string>  // 为了使用 std::string

class Executor
{
public:
    // 朝向枚举
    enum class Direction : char
    {
        N = 'N',
        S = 'S',
        E = 'E',
        W = 'W'
    };

    // 1. 初始化接口, 默认 (0,0,N)
    Executor(int32_t x = 0, int32_t y = 0, Direction heading = Direction::N);

    // 2. 批量执行指令
    // 指令字符串只包含 'M','L','R' (大小写敏感)
    void executeCommands(const std::string &commands);

    // 3. 查询当前状态
    int32_t getX() const noexcept { return x_; }
    int32_t getY() const noexcept { return y_; }
    Direction getHeading() const noexcept { return heading_; }

private:
    // 内部方法和成员变量
    void moveForward();
    void turnLeft();
    void turnRight();

    int32_t x_;
    int32_t y_;
    Direction heading_;
};

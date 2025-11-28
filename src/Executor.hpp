#pragma once

#include <cstdint>
#include <string>

class Executor
{
public:
    enum class Direction : char
    {
        N = 'N',
        S = 'S',
        E = 'E',
        W = 'W'
    };

    Executor(int32_t x = 0, int32_t y = 0, Direction heading = Direction::N);

    // 支持指令: M（前进）, L（左转）, R（右转）, F（切换加速状态）
    void executeCommands(const std::string &commands);

    int32_t getX() const noexcept { return x_; }
    int32_t getY() const noexcept { return y_; }
    Direction getHeading() const noexcept { return heading_; }

private:
    void moveForward();
    void turnLeft();
    void turnRight();

    int32_t x_;
    int32_t y_;
    Direction heading_;
    bool accelerated_; // 是否处于加速状态
};

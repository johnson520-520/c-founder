#include "Executor.hpp"

Executor::Executor(int x, int y, Direction dir)
    : x(x), y(y), dir(dir) {}

void Executor::executeCommand(char command)
{
    switch (command)
    {
    case 'F':
        fastMode = !fastMode;
        break;
    case 'B':
        backMode = !backMode;
        break;
    case 'M':
    {
        int steps = fastMode ? 2 : 1;
        if (backMode)
            moveBackward(steps);
        else
            moveForward(steps);
        break;
    }
    case 'L':
        if (backMode)
        {
            moveBackward(1);
            turnRight(); // 倒车状态下 L = 右转
        }
        else
        {
            turnLeft();
        }
        break;
    case 'R':
        if (backMode)
        {
            moveBackward(1);
            turnLeft(); // 倒车状态下 R = 左转
        }
        else
        {
            turnRight();
        }
        break;
    }
}

void Executor::moveForward(int steps)
{
    while (steps--)
    {
        switch (dir)
        {
        case Direction::N:
            y += 1;
            break;
        case Direction::E:
            x += 1;
            break;
        case Direction::S:
            y -= 1;
            break;
        case Direction::W:
            x -= 1;
            break;
        }
    }
}

void Executor::moveBackward(int steps)
{
    while (steps--)
    {
        switch (dir)
        {
        case Direction::N:
            y -= 1;
            break;
        case Direction::E:
            x -= 1;
            break;
        case Direction::S:
            y += 1;
            break;
        case Direction::W:
            x += 1;
            break;
        }
    }
}

void Executor::turnLeft()
{
    dir = static_cast<Direction>((static_cast<int>(dir) + 3) % 4);
}

void Executor::turnRight()
{
    dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
}

int Executor::getX() const { return x; }
int Executor::getY() const { return y; }
Direction Executor::getDirection() const { return dir; }
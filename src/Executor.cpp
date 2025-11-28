#include "Executor.hpp"
#include <stdexcept>

Executor::Executor(int32_t x, int32_t y, Direction heading)
    : x_(x), y_(y), heading_(heading), accelerated_(false) {}

void Executor::executeCommands(const std::string &commands)
{
    for (char cmd : commands)
    {
        switch (cmd)
        {
        case 'M':
            if (accelerated_)
            {
                moveForward();
                moveForward();
            }
            else
            {
                moveForward();
            }
            break;

        case 'L':
            if (accelerated_)
            {
                moveForward();
            }
            turnLeft();
            break;

        case 'R':
            if (accelerated_)
            {
                moveForward();
            }
            turnRight();
            break;

        case 'F':
            accelerated_ = !accelerated_;
            break;

        default:
            throw std::invalid_argument("Invalid command character");
        }
    }
}

void Executor::moveForward()
{
    switch (heading_)
    {
    case Direction::N:
        ++y_;
        break;
    case Direction::S:
        --y_;
        break;
    case Direction::E:
        ++x_;
        break;
    case Direction::W:
        --x_;
        break;
    }
}

void Executor::turnLeft()
{
    switch (heading_)
    {
    case Direction::N:
        heading_ = Direction::W;
        break;
    case Direction::W:
        heading_ = Direction::S;
        break;
    case Direction::S:
        heading_ = Direction::E;
        break;
    case Direction::E:
        heading_ = Direction::N;
        break;
    }
}

void Executor::turnRight()
{
    switch (heading_)
    {
    case Direction::N:
        heading_ = Direction::E;
        break;
    case Direction::E:
        heading_ = Direction::S;
        break;
    case Direction::S:
        heading_ = Direction::W;
        break;
    case Direction::W:
        heading_ = Direction::N;
        break;
    }
}

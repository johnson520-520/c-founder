#include "Executor.hpp"

Executor::Executor(int x, int y, Direction dir)
    : x(x), y(y), dir(dir) {}

void Executor::executeCommands(const std::string &commands)
{
    for (char c : commands)
    {
        executeCommand(c);
    }
}

void Executor::executeCommand(char command)
{
    switch (command)
    {
    case 'F':
        // F：加速状态开/关
        fastMode = !fastMode;
        pendingTurnRound = false;
        break;

    case 'B':
        // B：倒车状态开/关
        backMode = !backMode;
        pendingTurnRound = false;
        break;

    case 'T':
        // 记录：下一次如果收到 R 就当作 TR 掉头
        pendingTurnRound = true;
        break;

    case 'M':
    {
        // ====== 需求1 + 需求2 + 需求3：M ======
        // 普通：M 前进 1
        // F：   M 前进 2（一步一步）
        // B：   M 后退 1
        // F+B： M 后退 2（一步一步）
        int steps = fastMode ? 2 : 1;
        if (backMode)
            moveBackward(steps);
        else
            moveForward(steps);

        pendingTurnRound = false;
        break;
    }

    case 'L':
        // ====== L 依赖 F / B 组合 ======
        // 普通：L 左转 90 度，位置不变
        // F：   L 先前进 1 格，然后左转 90 度
        // B：   L 右转 90 度，位置不变
        // F+B： L 先倒退 1 格，然后右转 90 度

        pendingTurnRound = false; // TL 不是 TR

        if (!backMode && !fastMode)
        {
            // 普通
            turnLeft();
        }
        else if (!backMode && fastMode)
        {
            // 需求2：F + L
            moveForward(1);
            turnLeft();
        }
        else if (backMode && !fastMode)
        {
            // 需求3：B + L
            turnRight();
        }
        else // backMode && fastMode
        {
            // 需求3：F+B + L
            moveBackward(1);
            turnRight();
        }
        break;

    case 'R':
        if (pendingTurnRound)
        {
            // ===== TR 掉头 =====
            turnRound();
            pendingTurnRound = false;
        }
        else
        {
            // ===== R 依赖 F / B 组合 =====
            // 普通：R 右转 90 度，位置不变
            // F：   R 先前进 1 格，然后右转 90 度
            // B：   R 左转 90 度，位置不变
            // F+B： R 先倒退 1 格，然后左转 90 度

            if (!backMode && !fastMode)
            {
                turnRight();
            }
            else if (!backMode && fastMode)
            {
                moveForward(1);
                turnRight();
            }
            else if (backMode && !fastMode)
            {
                turnLeft();
            }
            else // backMode && fastMode
            {
                moveBackward(1);
                turnLeft();
            }
        }
        break;

    default:
        // 题目说不用考虑非法参数，这里直接忽略
        pendingTurnRound = false;
        break;
    }
}

// ===== 基础移动，只看朝向 =====

void Executor::moveForward(int steps)
{
    while (steps--)
    {
        switch (dir)
        {
        case Direction::N:
            ++y;
            break;
        case Direction::E:
            ++x;
            break;
        case Direction::S:
            --y;
            break;
        case Direction::W:
            --x;
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
            --y;
            break;
        case Direction::E:
            --x;
            break;
        case Direction::S:
            ++y;
            break;
        case Direction::W:
            ++x;
            break;
        }
    }
}

// ===== 纯转向 =====

void Executor::turnLeft()
{
    dir = static_cast<Direction>((static_cast<int>(dir) + 3) % 4);
}

void Executor::turnRight()
{
    dir = static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
}

// ===== TR 掉头实现 =====
//
// fastMode=false：左转 -> 前进 1 -> 左转
// fastMode=true： 前进 1 -> 左转 -> 前进 1 -> 左转
// 注意：这里完全不看 backMode，满足“TR 不受倒车影响”的约定
//
void Executor::turnRound()
{
    if (fastMode)
    {
        moveForward(1);
        turnLeft();
        moveForward(1);
        turnLeft();
    }
    else
    {
        turnLeft();
        moveForward(1);
        turnLeft();
    }
}

int Executor::getX() const { return x; }
int Executor::getY() const { return y; }
Direction Executor::getDirection() const { return dir; }

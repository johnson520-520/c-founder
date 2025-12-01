#pragma once

#include <string>

enum class Direction
{
    N,
    E,
    S,
    W
};

class Executor
{
public:
    // 默认初始化为 (0,0,N)
    Executor(int x = 0, int y = 0, Direction dir = Direction::N);

    // 执行单个控制指令：
    // M / L / R / F / B，和 T + R 组合成的 TR
    void executeCommand(char command);

    // 批量执行一串指令（需求里说的“批量指令执行”）
    void executeCommands(const std::string &commands);

    int getX() const;
    int getY() const;
    Direction getDirection() const;

private:
    int x, y;
    Direction dir;

    // 需求2：加速状态 F
    bool fastMode = false;

    // 需求3：倒车状态 B
    bool backMode = false;

    // 用来识别 TR 掉头的中间状态：
    // 收到 'T' 后置 true，下一次收到 'R' 时执行 turnRound()
    bool pendingTurnRound = false;

    // ===== 基础移动（只看 dir，不看 fast/back） =====
    void moveForward(int steps = 1);
    void moveBackward(int steps = 1);

    // 只改变朝向，不改位置（最基础的左/右转）
    void turnLeft();
    void turnRight();

    // ===== TR 掉头（实验 4）=====
    // 约定：
    //  - 不受倒车 B 的影响（内部一律按“前进 + 左转”来算）
    //  - fastMode = false：
    //        左转  → 前进 1 格 → 左转
    //  - fastMode = true：
    //        前进 1 格 → 左转 → 前进 1 格 → 左转
    void turnRound();
};

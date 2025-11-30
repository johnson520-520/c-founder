#include "Executor.hpp"
#include "gtest/gtest.h"
#include <string>

// 初始状态
TEST(ExecutorTest, InitialState)
{
    Executor e;
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 0);
    EXPECT_EQ(e.getDirection(), Direction::N);
}

// 需求1：基本指令 M/L/R
TEST(ExecutorTest, Requirement1_BasicMoveAndTurn)
{
    Executor e;
    e.executeCommands("MMRMM"); // 向北两步，右转向东，再两步

    EXPECT_EQ(e.getX(), 2);
    EXPECT_EQ(e.getY(), 2);
    EXPECT_EQ(e.getDirection(), Direction::E);
}

// 需求2：F 加速
TEST(ExecutorTest, Requirement2_FastMode)
{
    Executor e;
    e.executeCommands("FM"); // F + M：向北 2 格

    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 2);
    EXPECT_EQ(e.getDirection(), Direction::N);

    e.executeCommand('L'); // F 状态下 L：先前进 1，再左转
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 3);
    EXPECT_EQ(e.getDirection(), Direction::W);
}

// 需求3：B 倒车
TEST(ExecutorTest, Requirement3_BackMode)
{
    Executor e;
    e.executeCommands("BM"); // B + M：向南退 1 格

    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), -1);
    EXPECT_EQ(e.getDirection(), Direction::N);

    e.executeCommand('L'); // 倒车状态下 L：右转 90 度
    EXPECT_EQ(e.getDirection(), Direction::E);

    e.executeCommand('R'); // 倒车状态下 R：左转 90 度 -> 回到 N
    EXPECT_EQ(e.getDirection(), Direction::N);

    // 再来一次 B 取消倒车状态
    e.executeCommand('B');
    e.executeCommand('M');  // 现在是正常前进
    EXPECT_EQ(e.getY(), 0); // 从 -1 到 0
}

// F + B 叠加
TEST(ExecutorTest, Requirement3_FastAndBackTogether)
{
    Executor e;
    e.executeCommands("FBM"); // F + B + M：倒退 2 格

    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), -2);
    EXPECT_EQ(e.getDirection(), Direction::N);

    e.executeCommand('L'); // F+B 下 L：先倒退1，再右转
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), -3);
    EXPECT_EQ(e.getDirection(), Direction::E);

    e.executeCommand('R'); // F+B 下 R：先倒退1，再左转
    EXPECT_EQ(e.getX(), -1);
    EXPECT_EQ(e.getY(), -3);
    EXPECT_EQ(e.getDirection(), Direction::N);
}

// 你之前的 BLRM 用例（按需求规则重新写期望）
TEST(ExecutorTest, CombinedCommands_BLRM)
{
    Executor e;
    std::string commands = "BLRM";
    for (char c : commands)
        e.executeCommand(c);

    // 推导：
    // 初始 (0,0,N)
    // B: backMode=true
    // L: back + !fast -> 右转 90 度，位置不变 -> E
    // R: back + !fast -> 左转 90 度，位置不变 -> N
    // M: back + !fast -> 后退 1 格 -> (0,-1)
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), -1);
    EXPECT_EQ(e.getDirection(), Direction::N);
}

// TR：掉头指令
TEST(ExecutorTest, TurnRound_NormalAndFast)
{
    // 普通 TR
    Executor e1;
    e1.executeCommands("TR");

    // 普通：左转 -> 前进 1 -> 左转
    // N -> W -> (-1,0) -> S
    EXPECT_EQ(e1.getX(), -1);
    EXPECT_EQ(e1.getY(), 0);
    EXPECT_EQ(e1.getDirection(), Direction::S);

    // F 下 TR
    Executor e2;
    e2.executeCommands("FTR");

    // F：前进1 -> 左转 -> 前进1 -> 左转
    // (0,0,N) -> 前进(0,1) -> 左转(W) -> 前进(-1,1) -> 左转(S)
    EXPECT_EQ(e2.getX(), -1);
    EXPECT_EQ(e2.getY(), 1);
    EXPECT_EQ(e2.getDirection(), Direction::S);
}

// TR 在倒车状态下：TR 不受 B 影响
TEST(ExecutorTest, TurnRound_IgnoreBackMode)
{
    Executor e;
    e.executeCommands("BTR");

    // B 只改 backMode，TR 内部不看 backMode
    // 所以等价于普通 TR：结果同上 ( -1,0,S )
    EXPECT_EQ(e.getX(), -1);
    EXPECT_EQ(e.getY(), 0);
    EXPECT_EQ(e.getDirection(), Direction::S);
}

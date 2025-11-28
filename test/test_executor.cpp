#include <gtest/gtest.h>
#include "Executor.hpp"

using Dir = Executor::Direction;

TEST(ExecutorTest, DefaultInitialization)
{
    Executor e;
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 0);
    EXPECT_EQ(e.getHeading(), Dir::N);
}

TEST(ExecutorTest, CustomInitialization)
{
    Executor e(5, -3, Dir::S);
    EXPECT_EQ(e.getX(), 5);
    EXPECT_EQ(e.getY(), -3);
    EXPECT_EQ(e.getHeading(), Dir::S);
}

TEST(ExecutorTest, MoveForward)
{
    Executor e;
    e.executeCommands("M");
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 1);
}

TEST(ExecutorTest, TurnLeftRight)
{
    Executor e;
    e.executeCommands("L");
    EXPECT_EQ(e.getHeading(), Dir::W);
    e.executeCommands("R");
    EXPECT_EQ(e.getHeading(), Dir::N);
}

TEST(ExecutorTest, MixedCommands)
{
    Executor e(1, 1, Dir::N);
    e.executeCommands("MMRMMLM");
    EXPECT_EQ(e.getX(), 3);
    EXPECT_EQ(e.getY(), 4);
    EXPECT_EQ(e.getHeading(), Dir::N);
}

TEST(ExecutorTest, AcceleratedMove)
{
    Executor e;
    e.executeCommands("F"); // 加速状态
    e.executeCommands("M"); // 前进2格
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 2);
    e.executeCommands("F"); // 退出加速
    e.executeCommands("M"); // 前进1格
    EXPECT_EQ(e.getY(), 3);
}

TEST(ExecutorTest, AcceleratedTurnLeftRight)
{
    Executor e;
    e.executeCommands("F"); // 加速
    e.executeCommands("L"); // 前进1格 + 左转
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 1);
    EXPECT_EQ(e.getHeading(), Dir::W);

    e.executeCommands("R"); // 前进1格 + 右转
    EXPECT_EQ(e.getX(), -1);
    EXPECT_EQ(e.getY(), 1);
    EXPECT_EQ(e.getHeading(), Dir::N);
}

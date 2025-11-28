#include <gtest/gtest.h>
#include "Executor.hpp"

TEST(ExecutorTest, DefaultInitialization)
{
    Executor e;
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 0);
    EXPECT_EQ(e.getHeading(), Executor::Direction::N);
}

TEST(ExecutorTest, CustomInitialization)
{
    Executor e(5, -3, Executor::Direction::S);
    EXPECT_EQ(e.getX(), 5);
    EXPECT_EQ(e.getY(), -3);
    EXPECT_EQ(e.getHeading(), Executor::Direction::S);
}

TEST(ExecutorTest, MoveForward)
{
    Executor e;
    e.executeCommands("M");
    EXPECT_EQ(e.getX(), 0);
    EXPECT_EQ(e.getY(), 1); // N → +Y
    e.executeCommands("M");
    EXPECT_EQ(e.getY(), 2);
}

TEST(ExecutorTest, TurnLeft)
{
    Executor e;
    e.executeCommands("L");
    EXPECT_EQ(e.getHeading(), Executor::Direction::W);
    e.executeCommands("L");
    EXPECT_EQ(e.getHeading(), Executor::Direction::S);
    e.executeCommands("L");
    EXPECT_EQ(e.getHeading(), Executor::Direction::E);
    e.executeCommands("L");
    EXPECT_EQ(e.getHeading(), Executor::Direction::N);
}

TEST(ExecutorTest, TurnRight)
{
    Executor e;
    e.executeCommands("R");
    EXPECT_EQ(e.getHeading(), Executor::Direction::E);
    e.executeCommands("R");
    EXPECT_EQ(e.getHeading(), Executor::Direction::S);
    e.executeCommands("R");
    EXPECT_EQ(e.getHeading(), Executor::Direction::W);
    e.executeCommands("R");
    EXPECT_EQ(e.getHeading(), Executor::Direction::N);
}

TEST(ExecutorTest, MixedCommands)
{
    Executor e(1, 1, Executor::Direction::N);
    e.executeCommands("MMRMMLM");
    // 步骤拆解:
    // M -> (1,2) N
    // M -> (1,3) N
    // R -> (1,3) E
    // M -> (2,3) E
    // M -> (3,3) E
    // L -> (3,3) N
    // M -> (3,4) N
    EXPECT_EQ(e.getX(), 3);
    EXPECT_EQ(e.getY(), 4);
    EXPECT_EQ(e.getHeading(), Executor::Direction::N);
}
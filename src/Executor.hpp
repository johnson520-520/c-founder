#pragma once

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
    Executor(int x = 0, int y = 0, Direction dir = Direction::N);

    void executeCommand(char command);
    int getX() const;
    int getY() const;
    Direction getDirection() const;

private:
    int x, y;
    Direction dir;
    bool fastMode = false;
    bool backMode = false;

    void moveForward(int steps = 1);
    void moveBackward(int steps = 1);
    void turnLeft();
    void turnRight();
};

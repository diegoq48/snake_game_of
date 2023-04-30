#pragma once
#include <vector>

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

class Snake
{

private:
    unsigned int speed;
    unsigned int score;
    int goal;
    std::vector<std::vector<int>> body;
    Direction direction;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    bool crashed;

public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();
    int getScore()
    {
        return this->score;
    }
    void setScore(int score)
    {
        this->score = score;
    }
    int getSpeed()
    {
        return this->speed;
    }
    void setSpeed(int speed)
    {
        this->speed = speed;
    }
    int getGoal()
    {
        return this->goal;
    }
    void setGoal(int goal)
    {
        this->goal = goal;
    }
    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    void removeSection(int numOfSections, int recursionDepth = 0);
    bool isCrashed()
    {
        return this->crashed;
    }
    std::vector<int> getHead()
    {
        return this->body[0];
    }
    std::vector<int> getTail()
    {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody()
    {
        return this->body;
    }
    void setCrashed(bool crashed)
    {
        this->crashed = crashed;
    }
};

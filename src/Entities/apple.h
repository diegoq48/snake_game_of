#include "staticEntity.h"
#include "Snake.h"
class apple : public staticEntity{
private:
    int x,y;
    int cellSize;
    float foodSpawnTime;
    bool deadly;
    ofColor color;
public:
    apple(int Cellsize);
    virtual void draw(std::vector<std::vector<int>> snakeBody);
    ~apple();
    bool collidesWith(std::vector<std::vector<int>> snakeBody);
    int getX(){ return x; };
    int getY(){ return y; };
    
};

class PowerUp: public apple
{
protected:
    int x, y;
    int cellSize = 25;

public:
    PowerUp(int cellsize);
    virtual void applyPowerUp(Snake *snake) = 0; // apply the power-up effect
    virtual void draw(std::vector<std::vector<int>> snakeBody) = 0;                     // draw the power-up on the screen
    virtual bool collidesWith(std::vector<std::vector<int>> snakeBody);             // check if the power-up collides with a given position'
    virtual int getName() = 0;
};

class SpeedPowerUp : public PowerUp
{
public:
    SpeedPowerUp(int cellSize);
    void applyPowerUp(Snake *snake);
    void draw(std::vector<std::vector<int>> snakeBody);
    int getName() { return 0; }
};

class BetterApple : public PowerUp
{
public:
    BetterApple(int cellsize);
    void applyPowerUp(Snake *snake);
    void draw(std::vector<std::vector<int>> snakeBody);
    int getName() { return 1; }
};

class GodMode : public PowerUp
{
public:
    GodMode(int cellsize);
    void applyPowerUp(Snake *snake);
    void draw(std::vector<std::vector<int>> snakeBody);
    int getName() { return 2; }
    };

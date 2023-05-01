#pragma once
#include "ofMain.h"
#include "Snake.h"

class PowerUp
{
protected:
    int x, y;
    int duration; // the duration of the power-up effect
    int cellSize = 25;

public:
    PowerUp(int x, int y, int duration_);
    virtual void applyPowerUp(Snake *snake) = 0; // apply the power-up effect
    virtual void draw() = 0;                     // draw the power-up on the screen
    bool collidesWith(int x, int y);             // check if the power-up collides with a given position'
    virtual int getName() = 0;
};

class SpeedPowerUp : public PowerUp
{
public:
    SpeedPowerUp(int x, int y, int duration_);
    void applyPowerUp(Snake *snake);
    void draw();
    int getName() { return 0; }
};

class BetterApple : public PowerUp
{
public:
    BetterApple(int x, int y, int duration_);
    void applyPowerUp(Snake *snake);
    void draw();
    int getName() { return 1; }
};

class GodMode : public PowerUp
{
public:
    GodMode(int x, int y, int duration_);
    void applyPowerUp(Snake *snake);
    void draw();
    int getName() { return 2; }
    };

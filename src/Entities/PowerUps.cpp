#include "PowerUps.h"

PowerUp::PowerUp(int x, int y, int duration_)
    : x(x), y(y), duration(duration_) {}

bool PowerUp::collidesWith(int x, int y)
{
    return (x == x && y == y);
}

SpeedPowerUp::SpeedPowerUp(int x, int y, int duration_)
    : PowerUp(x, y, duration_) {}

void SpeedPowerUp::applyPowerUp(Snake *snake)
{
    snake->setSpeed(snake->getSpeed() + 1);
}

void SpeedPowerUp::draw()
{
    ofSetColor(ofColor::cyan);
    ofDrawCircle(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, cellSize / 2);
}

BetterApple::BetterApple(int x, int y, int duration_)
    : PowerUp(x, y, duration_) {}

void BetterApple::applyPowerUp(Snake *snake)
{
    snake->grow();
}

void BetterApple::draw()
{
    ofSetColor(ofColor::greenYellow);
    ofDrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize);
}

GodMode::GodMode(int x, int y, int duration_)
    : PowerUp(x, y, duration_) {}

void GodMode::applyPowerUp(Snake *snake)
{
    // snake->activateGodMode(duration);
}

void GodMode::draw()
{
    ofSetColor(ofColor::magenta);
    ofDrawTriangle(x * cellSize + cellSize / 2, y * cellSize,
                   x * cellSize, y * cellSize + cellSize,
                   x * cellSize + cellSize, y * cellSize + cellSize);
}

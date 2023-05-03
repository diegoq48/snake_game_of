#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "PowerUps.h"
#include "apple.h"

class GameState : public State
{
public:
    GameState();
    ~GameState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void PowerSpawner();
    void drawPower();
    void drawStartScreen();
    void drawLostScreen();
    void drawBoardGrid();

    Snake *snake;

    bool foodSpawned = false;
    bool PowerSpawned = false;

    int currentFoodX;
    int currentFoodY;
    int currentPowerX;
    int currentPowerY;

    int boardSizeWidth, boardSizeHeight;
    int cellSize; // Pixels
    bool paused = false;

private:
    std::vector<std::unique_ptr<staticEntity>> staticEntityVector;
    std::vector<std::unique_ptr<PowerUp>> powerUps;

    unsigned int tick = 0;
    unsigned int entityCount = 1;
    bool rottedFood = false;
};
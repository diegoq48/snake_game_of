#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "staticEntity.h"

class GameState : public State
{
public:
    GameState();
    ~GameState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void foodSpawner();
    void drawFood();
    void drawStartScreen();
    void drawLostScreen();
    void drawBoardGrid();

    Snake *snake;

    bool foodSpawned = false;

    int currentFoodX;
    int currentFoodY;

    int boardSizeWidth, boardSizeHeight;
    int cellSize; // Pixels
    bool paused = false;

private:
    std::vector<std::unique_ptr<staticEntity>> staticEntityVector;
    unsigned int tick = 0;
    unsigned int entityCount = 1;
    int goal = 50;
    int getGoal() { return goal; };
    void setGoal(int newGoal) { goal = newGoal; };
};
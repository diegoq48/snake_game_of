#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "PowerUps.h"
#include "apple.h"
#include "search_traversal.h"

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
    void drawShortestPath();
    bool paused = false;
    void despawnFood();
    std::vector<std::vector<int>> globalGrid;

private:
    std::vector<std::unique_ptr<staticEntity>> staticEntityVector;
    //int foodSpawnRate = ofGetTimeMillis() + 5000;

    std::vector<std::unique_ptr<PowerUp>> powerUps;
    bool spacePressed = false;
    unsigned int tick = 0;
    unsigned int entityCount = 1;
    std::vector<std::vector<int>> lastBody;
    int appleColorTick = 0; // Used to change the color of the apple
    unsigned int foodSpawnTime = 0;
   unsigned int foodAge = 0;

};
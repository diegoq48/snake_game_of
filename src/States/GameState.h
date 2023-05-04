#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "apple.h"
#include <memory>
#include <vector>
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
    //void PowerSpawner();
    //void drawPower();
    void drawStartScreen();
    void keyReleased(int key);
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
    // make a sharedPtr of type search_traversal
    int appleTracker = 0;
    std::shared_ptr<searchAlgorithm> search;
    // int foodSpawnRate = ofGetTimeMillis() + 5000;

    std::unique_ptr<PowerUp> powerUp = nullptr;

    bool spacePressed = false;
    int priorScore = 0;
    unsigned int tick = 0;
    unsigned int entityCount = 1;
    std::vector<std::vector<int>> lastBody;
    std::unique_ptr<PowerUp> activePowerUp = nullptr;
    int ticksOnGodModeActivation = 0;
    int ticksOnSpeedModeActivation = 0;

};
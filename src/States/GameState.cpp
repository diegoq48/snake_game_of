#include "GameState.h"
//--------------------------------------------------------------
GameState::GameState()
{
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    search = std::make_shared<searchAlgorithm>();
    ofSetFrameRate(60);
    globalGrid = search->createGrid(boardSizeHeight, boardSizeWidth);
}
//--------------------------------------------------------------
GameState::~GameState()
{
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset()
{
    if (!paused)
    {
        delete snake;
        snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
        foodSpawned = false;
        staticEntityVector.clear();
        entityCount = 1;
        tick = 0;
        appleTracker = 0;
        priorScore = 0;
        activePowerUp = nullptr;
        powerUp = nullptr;
        ticksOnGodModeActivation = 0;
        ticksOnSpeedModeActivation = 0;
        lastBody.clear();

    }

    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update()
{
    tick++;
    if (this->tick == this->ticksOnGodModeActivation + 300 && this->activePowerUp != nullptr)
    {
        this->activePowerUp->deactivate(snake);
        this->activePowerUp = nullptr;
    }
    if (this->tick == this->ticksOnSpeedModeActivation +350 && this->activePowerUp != nullptr){
        this->activePowerUp->deactivate(snake);
        this->activePowerUp = nullptr;
    }
    // checks if the snake has crashed if so it ends the game
    if (snake->isCrashed())
    {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }
    if (snake->getScore() % 50 == 0 && snake->getScore() != priorScore){
        if (foodSpawned && !PowerSpawned){
            // search the staticEntityVector for the apple and remove it
            for (auto it = staticEntityVector.begin(); it != staticEntityVector.end(); it++)
            {
                if(dynamic_cast<apple*>(it->get()) != nullptr){
                    staticEntityVector.erase(it);
                    break;
                }
            }
            switch (appleTracker){
                case 0:
                    staticEntityVector.push_back(std::make_unique<SpeedPowerUp>(cellSize));
                    PowerSpawned = true;
                    foodSpawned = true;
                    appleTracker++;
                    break;
                case 1:
                    staticEntityVector.push_back(std::make_unique<BetterApple>(cellSize));
                    PowerSpawned = true;
                    foodSpawned = true;
                    appleTracker++;
                    break;
                case 2:
                    staticEntityVector.push_back(std::make_unique<GodMode>(cellSize));
                    PowerSpawned = true;
                    foodSpawned = true;
                    appleTracker = 0;
                    break;
                default:
                    break;
            }
        priorScore = snake->getScore();
        }
    }
    // creates an apple object to be displayed on the screen and assigns currentFoodX and currentFoodY to the apple's x and y
    if (!foodSpawned)
    {
        staticEntityVector.push_back(std::make_unique<apple>(cellSize));
        for (auto &entity : staticEntityVector)
        {
            apple *applePtr = dynamic_cast<apple *>(entity.get());
            if (applePtr != nullptr)
            {
                currentFoodX = applePtr->getX();
                currentFoodY = applePtr->getY();
                break;
            }
        }
        foodSpawned = true;
    }
    // updates the lastBody position of the snake
    this->lastBody = snake->getBody();

    // itterates through all of the static entities in the game and checks if the snake has collided with any of them calling their respective collidesWith functions
    for (auto it = staticEntityVector.begin(); it != staticEntityVector.end(); it++)
    {
        if ((*it)->collidesWith(snake->getBody()))
        {
            if (dynamic_cast<SpeedPowerUp *>(it->get()) != nullptr)
            {
                snake->setScore(snake->getScore() + 10);
                snake->setSpeed(snake->getSpeed() + 0.5);
                PowerSpawned = false;
                foodSpawned = false;
                //move the it pointer to the powerUps vector 
                this->powerUp = (std::move(std::unique_ptr<PowerUp>(dynamic_cast<PowerUp*>(it->release()))));
                staticEntityVector.erase(it);

                break;
            }
            else if (dynamic_cast<GodMode *>(it->get()) != nullptr)
            {
                snake->setScore(snake->getScore() + 10);
                foodSpawned = false; 
                PowerSpawned = false;
                this->powerUp = (std::move(std::unique_ptr<PowerUp>(dynamic_cast<PowerUp*>(it->release()))));     
                staticEntityVector.erase(it);
                break;
            }
            else if (dynamic_cast<BetterApple *>(it->get()) != nullptr)
            {
                snake->setScore(snake->getScore() + 20);
                foodSpawned = false;
                PowerSpawned = false;
                snake->grow();
                snake->grow();
                staticEntityVector.erase(it);
                break;
            }
            else if (dynamic_cast<apple *>(it->get()) != nullptr)
            {
                snake->grow();
                snake->setScore(snake->getScore() + 10);
                foodSpawned = false;
                staticEntityVector.erase(it);
                break;
            }
            else
            {
                if(!snake->getGod()){
                    snake->setCrashed(true);
                    return;
                }
            }
        }
    }
    // moves the snake every 10 frames
    if (ofGetFrameNum() % 10 == 0)
    {
        snake->update();
        // updates the global grid in order to check for collisions with the body
        search->updateGrid(globalGrid, snake->getBody(), 1);
    }

    if (tick % 60 == 0)
    {
        bool isColliding = true;
        while (isColliding)
        {
            int x = ofRandom(1, boardSizeWidth - 1);
            int y = ofRandom(1, boardSizeHeight - 1);
            staticEntity newEntity(x, y, true, entityCount, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
            isColliding = false;
            for (int i = 0; i < newEntity.getID(); i++)
            {
                if (newEntity.getX() + i >= boardSizeWidth - 1)
                {
                    break;
                }
                if (newEntity.getY() >= boardSizeHeight - 1)
                {
                    break;
                }
                search->updateGrid(globalGrid, newEntity.getX() + i, newEntity.getY(), 1);
            }

            if (newEntity.collidesWith(snake->getBody()))
            {
                isColliding = true;
                break;
            }

            if (!isColliding)
            {
                staticEntityVector.push_back(std::make_unique<staticEntity>(newEntity));
                entityCount++;
            }
        }
    }

    // deletes the first static entity in the vector every 2 seconds
    // except for the apple
    if (tick % 120 == 0)
    {
        if (dynamic_cast<apple *>(staticEntityVector[0].get()))
        {
            staticEntityVector.erase(staticEntityVector.begin() + 1);
        }
        else
        {
            staticEntityVector.erase(staticEntityVector.begin());
        }
        entityCount--;
    }

    // win or continue
    if (snake->getScore() >= snake->getGoal())
    {
        setFinished(true);
        this->setNextState("WinState");
        snake->setGoal(snake->getGoal() + 200);
    }
    // Deletes the apple every 30secs
    if (tick % 900 == 0)
    {
        // find and delete the apple
        for (auto it = staticEntityVector.begin(); it != staticEntityVector.end(); it++)
        {
            if (dynamic_cast<PowerUp *>(it->get()))
            {
                break;
            }
            if (dynamic_cast<apple *>(it->get()))
            {
                staticEntityVector.erase(it);
                break;
            }
        }
        foodSpawned = false;
        
    }
}
// forcing an itterative method to be recursive discousting
void GameState::drawShortestPath()
{
    search->updateGrid(globalGrid, lastBody, 0);
    std::pair<int, int> head = {snake->getHead()[0], snake->getHead()[1]};
    std::pair<int, int> food = {currentFoodX, currentFoodY};
    search->updateGrid(globalGrid, snake->getBody(), 1);
    this->lastBody = snake->getBody();
    std::queue<std::tuple<int, int, int>> queue;
    queue.push({head.first, head.second, 0});
    std::set<std::pair<int, int>> visited = {head};
    std::map<std::pair<int, int>, std::pair<int, int>> parent = {{head, {}}};
    auto [path, steps] = search->recursive_bfs(globalGrid, head, food, queue, visited, parent);
    search->updateGrid(globalGrid, lastBody, 0);
    ofSetColor(ofColor::blue);
    for (auto &e : path)
    {
        ofDrawRectangle(e.first * cellSize, e.second * cellSize, cellSize, cellSize);
    }
}

void GameState::draw()
{
    drawBoardGrid();
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Score:" + ofToString(snake->getScore()), 10, 20);
    ofDrawBitmapString("Goal:" + ofToString(snake->getGoal()), 10, 40);
    ofDrawBitmapString("Speed:" + ofToString(snake->getSpeed()), 10, 60);
    if (this->activePowerUp != nullptr)
    ofDrawBitmapString("Current PowerUp:" + this->activePowerUp->getName(), 10, 80);
    if (this->powerUp != nullptr){
    ofDrawBitmapString("Cached PowerUp:" + ofToString(this->powerUp->getName()), 10, 100);}
    //ofDrawBitmapString("PowerUps:" + ofToString(powerUps), 10, 80);
    //ofDrawBitmapString("Colllected PowerUps:" + ofToString(000), 10, 100);

    snake->draw();
    for (unsigned int i = 0; i < staticEntityVector.size(); i++)
    {
        staticEntityVector[i]->draw(snake->getBody());
    }
    if (spacePressed)
    {
        drawShortestPath();
    }
    
}
//--------------------------------------------------------------
void GameState::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        spacePressed = !spacePressed;
        break;
    case OF_KEY_LEFT:
        snake->changeDirection(LEFT);
        break;
    case OF_KEY_RIGHT:
        snake->changeDirection(RIGHT);
        break;
    case OF_KEY_UP:
        snake->changeDirection(UP);
        break;
    case OF_KEY_DOWN:
        snake->changeDirection(DOWN);
        break;
    case 'a':
        snake->setScore(snake->getScore() + 10);
        snake->grow();
        for (unsigned int i = 0; i < snake->getBody().size(); i++)
        {
            cout << snake->getBody()[i][0] << " " << snake->getBody()[i][1] << endl;
        }
        break;
    case 'u':
        // removes the last segment of the snake
        if (snake->getBody().size() > 2)
        {
            snake->removeSection(1);
        }

        // print the snake vector
        for (unsigned int i = 0; i < snake->getBody().size(); i++)
        {
            cout << snake->getBody()[i][0] << " " << snake->getBody()[i][1] << endl;
        }
        break;
    case 'p':
        setFinished(true);
        setNextState("pauseState");
        break;

    case 'b':
        if (powerUp != nullptr){
        this->powerUp->applyPowerUp(snake);
        this->activePowerUp = std::move(this->powerUp);
        this->powerUp = nullptr;

        
        if (this->activePowerUp->getName() == "GodMode"){
            this->ticksOnGodModeActivation = this->tick;
        }
        if (this->activePowerUp->getName() == "Speed"){
            this->ticksOnSpeedModeActivation = this->tick;
        }                                                                           

    default:
        break;
    }
}
}

void GameState::keyReleased(int key)
{
    switch (key)
    {
    case 'e':
        spacePressed = !spacePressed;
        break;

    default:
        break;
    }
}

// Draws the grid
void GameState::drawBoardGrid()
{
    ofSetBackgroundColor(33, 4, 43);

    ofDrawGrid(25, 64, false, false, false, true);
}

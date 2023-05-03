#include "GameState.h"
//--------------------------------------------------------------
GameState::GameState()
{
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
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
        std::cout << "Game reset" << std::endl;
        std::cout << paused << std::endl;
        staticEntityVector.clear();
        entityCount = 1;
        tick = 0;
    }

    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void GameState::update()
{
    if (!foodSpawned){
        staticEntityVector.push_back(std::make_unique<apple>(cellSize));
        foodSpawned = true;
    }
    tick++;
    if (snake->isCrashed())
    {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }
    for (auto it = staticEntityVector.begin(); it != staticEntityVector.end(); it++)
    {
        if ((*it)->collidesWith(snake->getBody()))
        {
            if(dynamic_cast<apple*>(it->get()) != nullptr)
            {
                snake->grow();
                foodSpawned = false;
                staticEntityVector.erase(it);
                break;
            }
            else{
            snake->setCrashed(true);
            return;
            }
        }
    }
    for (auto it = powerUps.begin(); it != powerUps.end(); it++)
    {
        if ((*it)->collidesWith(snake->getHead()[0], snake->getHead()[1]))
        {
            (*it)->applyPowerUp(this->snake);
            // make a dynamic cast to check the type of the power-up and then make a switch 
            // to check which power-up it is and then respawn it
            switch ((*it)->getName())
            {
            case 0:
                powerUps.push_back(std::make_unique<SpeedPowerUp>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 10));
                break;
            case 1:
                powerUps.push_back(std::make_unique<BetterApple>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 10));
                break;
            case 2:
                // god mode powerup 
                powerUps.push_back(std::make_unique<GodMode>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 10));
                break;
            default:
                break;
            }

            powerUps.erase(it);
            break;
        }
    }

    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY)
    {
        snake->grow();
        snake->setScore(snake->getScore() + 10);
        snake->setSpeed(snake->getSpeed() + 1);
        foodSpawned = false;
    }

    
    if (ofGetFrameNum() % 10 == 0)
    {
        snake->update();
    }
    /*    if(tick % 60 == 0){

           staticEntityVector.push_back(std::make_unique<staticEntity>(ofRandom(1, boardSizeWidth-1), ofRandom(1, boardSizeHeight-1), true, entityCount, ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255))));
           entityCount++;
       } */
    if (tick % 60 == 0)
    {
        // sets a boolian value to true by default
        bool isColliding = true;
        while (isColliding)
        {
            int x = ofRandom(1, boardSizeWidth - 1);
            int y = ofRandom(1, boardSizeHeight - 1);
            staticEntity newEntity(x, y, true, entityCount, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
            isColliding = false;

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
    if (tick % 120 == 0)
    {
        if (dynamic_cast<apple *>(staticEntityVector[0].get()))
        {
            staticEntityVector.erase(staticEntityVector.begin()+1);
        }
        else{
        staticEntityVector.erase(staticEntityVector.begin());
        }
        entityCount--;
    }

    // win or continue
    if (snake->getScore() >= snake->getGoal())
    {
        setFinished(true);
        this->setNextState("WinState");
        snake->setGoal(snake->getGoal() + 50);
    }
    if (tick % 900 == 0)
    {
        //find and delete the apple 
        for (auto it = staticEntityVector.begin(); it != staticEntityVector.end(); it++)
        {
            if (dynamic_cast<apple *>(it->get()))
            {
                staticEntityVector.erase(it);
                break;
            }
        }
    }
}
//--------------------------------------------------------------
void GameState::draw()
{
    ofDrawBitmapString("Score:" + ofToString(snake->getScore()), 10, 20);
    ofDrawBitmapString("Goal:" + ofToString(snake->getGoal()), 10, 40);
    ofDrawBitmapString("Speed:" + ofToString(snake->getSpeed()), 10, 60);
    drawBoardGrid();
    snake->draw();
    for (unsigned int i = 0; i < staticEntityVector.size(); i++)
    {
        staticEntityVector[i]->draw(snake->getBody());
    }
    drawPower();
}
//--------------------------------------------------------------
void GameState::keyPressed(int key)
{

    // if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN) { return; }

    switch (key)
    {
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
    default:
        break;
    }
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void GameState::PowerSpawner()
{

    if (!PowerSpawned)
    {
        bool isInSnakeBody;
        do
        {
            isInSnakeBody = false;

            powerUps.push_back(std::make_unique<SpeedPowerUp>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 300));
            powerUps.push_back(std::make_unique<BetterApple>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 300));
            powerUps.push_back(std::make_unique<GodMode>(ofRandom(1, boardSizeWidth - 1), ofRandom(1, boardSizeHeight - 1), 300));

            for (unsigned int i = 0; i < snake->getBody().size(); i++)
            {
                if (currentPowerX == snake->getBody()[i][0] and currentPowerY == snake->getBody()[i][1])
                {
                    isInSnakeBody = true;
                }
            }
        } while (isInSnakeBody);
        PowerSpawned = true;
    }
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void GameState::drawPower()
{
    if (PowerSpawned)
    {
        for (const auto &powerUp : powerUps)
        {
            powerUp->draw();
        }
    }
}
//--------------------------------------------------------------
void GameState::drawBoardGrid()
{
    ofSetBackgroundColor(33, 4, 43);

    ofDrawGrid(25, 64, false, false, false, true);

    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------


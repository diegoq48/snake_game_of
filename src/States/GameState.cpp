#include "GameState.h"
//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);

}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    if(!paused){
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
void GameState::update() {
    tick++;
    if(snake->isCrashed()) {
        this->setNextState("looseState");
        this->setFinished(true);
        return;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        snake->grow();
        snake->setScore(snake->getScore() + 10);
        snake->setSpeed(snake->getSpeed() + 1);
        foodSpawned = false;
    }

    foodSpawner();
    if(ofGetFrameNum() % 10 == 0) {
        snake->update();
    }
    if(tick % 300 == 0){
        staticEntityVector.push_back(std::make_unique<staticEntity>(ofRandom(1, boardSizeWidth-1), ofRandom(1, boardSizeHeight-1), true, entityCount, ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255))));
        entityCount++;
    }
    for(unsigned int i = 0; i < staticEntityVector.size(); i++){
        if(staticEntityVector[i]->collidesWith(snake->getHead()[0], snake->getHead()[1])){
            snake->setCrashed(true);
        }
    }
    if(tick % 1200 == 0){
        staticEntityVector.erase(staticEntityVector.begin());
    }



}
//--------------------------------------------------------------
void GameState::draw() {
    ofDrawBitmapString("Score:" + ofToString(snake->getScore()), 10, 20);
    ofDrawBitmapString("Speed:" + ofToString(snake->getSpeed()), 10, 40);
    drawBoardGrid();
    snake->draw();
    for (unsigned int i = 0; i < staticEntityVector.size(); i++){
        staticEntityVector[i]->draw();
    }
    drawFood();
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    //if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN) { return; }

    switch(key) {
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
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
            cout << snake->getBody()[i][0] << " " << snake->getBody()[i][1] << endl;
            }
            break;
        case 'u':
            //removes the last segment of the snake
           if(snake->getBody().size() > 2) {
                snake->removeSection(1);
            } 

            //print the snake vector 
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
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
void GameState::foodSpawner() {
    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    ofSetColor(ofColor::red);
    if(foodSpawned) {
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    return;
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------


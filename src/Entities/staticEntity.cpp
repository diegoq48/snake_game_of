#include "staticEntity.h"

staticEntity::staticEntity(int x, int y, bool deadly, int entityID, ofColor color) {
    this->xPosition = x;
    this->yPosition = y;
    this->isDeadly = deadly;
    this->entityID = entityID;
    this->color = ofColor::orange;
}

staticEntity::~staticEntity() {
    // TODO Auto-generated destructor stub
}

void staticEntity::update() {

}

void staticEntity::draw(std::vector<std::vector<int>> snakeBody) {
    // Define a color for the rectangles
    // Draw a rectangle for each entity
    for(int i = 0; i < entityID; i++) {
        // Ineffient but creates the old glitchy effect that we're looking for 
        ofSetColor(ofColor(ofRandom(255), ofRandom(255), ofRandom(255)));
        ofDrawRectangle((this->xPosition + i) * 25, this->yPosition * 25, 25, 25);
    }
    

    // Check if the entity is in the snake body and update its deadly status
    for(unsigned int i = 0; i < snakeBody.size(); i++) {
        if(this->xPosition == snakeBody[i][0] && this->yPosition == snakeBody[i][1]) {
            this->isDeadly = false;
            return;
        }
    }
    this->isDeadly = true;
}


bool staticEntity::collidesWith(std::vector<std::vector<int>> snakeBody) {
    // Check if the entity's position collides with any position in the snake's body
    for (int i = this->xPosition; i < this->xPosition + this->entityID; i++) {
        for (unsigned int j = 0; j < snakeBody.size(); j++) {
            if (i == snakeBody[j][0] && this->yPosition == snakeBody[j][1]) {
                return true;
            }
        }
    }
    return false;
}

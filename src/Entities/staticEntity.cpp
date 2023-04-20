#include "staticEntity.h"

staticEntity::staticEntity(int x, int y, bool deadly, int entityID, ofColor color) {
    this->xPosition = x;
    this->yPosition = y;
    this->isDeadly = deadly;
    this->entityID = entityID;
    this->color = color;
}

staticEntity::~staticEntity() {
    // TODO Auto-generated destructor stub
}

void staticEntity::update() {

}

void staticEntity::draw() {
    ofSetColor(this->color);
    ofDrawRectangle(this->xPosition*25, this->yPosition*25, (25*entityID)%500 , (25*entityID)%500);
}

bool staticEntity::collidesWith(int x, int y) {
        //return (x < this->xPosition *25 + 25*entityID && x > this->xPosition *25 && y < this->yPosition *25 + 25*entityID && y > this->yPosition *25);
    // return if the x and y are within the boundaries of the drawn rectangle
    // print all of the variables being compared
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "xPosition: " << this->xPosition << std::endl;
    std::cout << "yPosition: " << this->yPosition << std::endl;
    std::cout << "entityID: " << this->entityID << std::endl;

    int rectWidth = 25 * this->entityID % 500; // calculate the width of the rectangle
    int rectHeight = 25 * this->entityID / 500 * 25; // calculate the height of the rectangle

    if (x >= this->xPosition*25 && x <= this->xPosition*25 + rectWidth
        && y >= this->yPosition*25 && y <= this->yPosition*25 + rectHeight) {
        std::cout << "collides with" << std::endl;
        return true;
    }
    return false;

}   
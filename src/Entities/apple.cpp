#include "apple.h" 

apple::apple(int Cellsize): staticEntity(0,0,false,0,ofColor::red)
{
    this->deadly = false;
    this->x = ofRandom(1,63);
    this->y = ofRandom(1,35);
    this->foodSpawnTime = ofGetElapsedTimef();
    this->cellSize = Cellsize;
    this->color = ofColor::red;
}

void apple::draw(std::vector<std::vector<int>> snakeBody)
{
    // Calculate the elapsed time since the food was spawned
    float elapsedTime = ofGetElapsedTimef() - foodSpawnTime;

    // Calculate the ratio of elapsed time to 30 seconds
    float timeRatio = elapsedTime / 30.0f;

    // Clamp the time ratio to the range [0, 1]
    timeRatio = ofClamp(timeRatio, 0.0f, 1.0f);

    // Interpolate between red and brown based on the time ratio
    ofColor foodColor = ofColor::red.getLerped(ofColor(150, 75, 0), timeRatio);

    // Set the food color
    ofSetColor(foodColor);

    // Draw the food
    ofDrawRectangle(this->x * this->cellSize, this->y * this->cellSize, this->cellSize, this->cellSize);
    return;
}

bool apple::collidesWith(std::vector<std::vector<int>> snakeBody)
{
    // Check if the entity's position collides with any position in the snake's body
    return (this->x == snakeBody[0][0] && this->y == snakeBody[0][1]);
}
apple::~apple(){
    std::cout << "apple deleted" << std::endl;
}

PowerUp::PowerUp(int cellSize) : apple(cellSize){
    this->x = ofRandom(0, 63);
    this->y = ofRandom(0, 35);
}

bool PowerUp::collidesWith(std::vector<std::vector<int>> snakeBody)
{
    return (this->x == snakeBody[0][0] && this->y == snakeBody[0][1]);
}

SpeedPowerUp::SpeedPowerUp(int cellsize): PowerUp(cellsize){
    this->x = ofRandom(0, 63);
    this->y = ofRandom(0, 35);
}

void SpeedPowerUp::applyPowerUp(Snake *snake)
{
    snake->setSpeed(snake->getSpeed() + 5);
}


void SpeedPowerUp::draw(std::vector<std::vector<int>> snakeBody)
{
    std::cout << "drawing speed powerup" << std::endl;
    ofSetColor(ofColor::cyan);
    ofDrawCircle(this->x * cellSize + cellSize / 2, this->y * cellSize + cellSize / 2, cellSize / 2);
}

BetterApple::BetterApple(int cellsize): PowerUp(cellsize){
    this->x = ofRandom(0, 63);
    this->y = ofRandom(0, 35);
}

void BetterApple::applyPowerUp(Snake *snake)
{
    snake->grow();
}

void BetterApple::draw(std::vector<std::vector<int>> snakeBody)
{
    std::cout << "drawing better apple" << std::endl;
    ofSetColor(ofColor::greenYellow);
    ofDrawRectangle(this->x * cellSize, this->y * cellSize, cellSize, cellSize);
}

GodMode::GodMode(int cellsize): PowerUp(cellsize){
    this->x = ofRandom(0, 63);
    this->y = ofRandom(0, 35);
}
void GodMode::applyPowerUp(Snake *snake)
{
    // snake->activateGodMode(duration);
}

void GodMode::draw(std::vector<std::vector<int>> snakeBody)
{
    std::cout << "drawing god mode" << std::endl;
    ofSetColor(ofColor::magenta);
    ofDrawTriangle(this->x * cellSize + cellSize / 2, this->y * cellSize,
                   this->x * cellSize, this->y * cellSize + cellSize,
                   this->x * cellSize + cellSize, this->y * cellSize + cellSize);
}

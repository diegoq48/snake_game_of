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
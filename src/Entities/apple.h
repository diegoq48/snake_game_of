#include "staticEntity.h"
class apple : public staticEntity{
private:
    int x,y;
    int cellSize;
    float foodSpawnTime;
    bool deadly;
    ofColor color;
public:
    apple(int Cellsize);
    void draw(std::vector<std::vector<int>> snakeBody);
    ~apple();
    bool collidesWith(std::vector<std::vector<int>> snakeBody);
    int getX(){ return x; };
    int getY(){ return y; };
    
};

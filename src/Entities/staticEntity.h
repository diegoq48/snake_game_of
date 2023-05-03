#include "entity.h"
#include <vector>

class staticEntity: public Entity {
    private:
        int xPosition;
        int yPosition;
        bool isDeadly;
        ofColor color;
        int entityID;
    public:
        staticEntity (int x, int y, bool deadly, int entityID, ofColor color);
        ~staticEntity();
        void update();
        void draw(std::vector<std::vector<int>> snakeBody);
        
        bool collidesWith( std::vector<std::vector<int>> snakeBody);
        int getX(){ return xPosition; };
        int getY(){ return yPosition; };
        int getID(){ return entityID; };

};


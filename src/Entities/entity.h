#include "ofMain.h"

class Entity {
    public:
        Entity(){
        }
        ~Entity(){
        }
        virtual void update() = 0;
        virtual void draw(std::vector<std::vector<int>> snakeBody) = 0;
        virtual bool collidesWith(std::vector<std::vector<int>> snakeBody) = 0;

    protected:
    private:
        int xPosition; 
        int yPosition; 
        bool isDeadly;


};

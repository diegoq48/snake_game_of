#include "ofMain.h"

class Entity {
    public:
        Entity(){
            std::cout << "Entity created" << std::endl;
        }
        ~Entity(){
            std::cout << "Entity destroyed" << std::endl;
        }
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual bool collidesWith(int x, int y) = 0;

    protected:
    private:
        int xPosition; 
        int yPosition; 
        bool isDeadly;


};

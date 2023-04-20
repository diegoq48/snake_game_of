#include "entity.h"

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
        void draw();
        bool collidesWith(int x, int y);
};


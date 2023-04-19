#include "State.h"
#include "ofMain.h"


class looseState : public State {
    public:
        looseState();
        ~looseState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void foodSpawner();
        void drawFood();
        void drawStartScreen();
        void drawLostScreen();
        void drawBoardGrid();
};
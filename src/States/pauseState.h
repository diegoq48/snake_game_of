#include "State.h"

class pauseState : public State {
    public:
        pauseState();
        ~pauseState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        
};
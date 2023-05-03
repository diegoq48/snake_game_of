#include "State.h"
#include "ofMain.h"

class LoseState : public State
{
private:
    ofImage gameover;

public:
    LoseState();
    ~LoseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void foodSpawner();
    void drawFood();
    void drawStartScreen();
    void mousePressed(int x, int y, int button);
    void drawLostScreen();
    void drawBoardGrid();
};
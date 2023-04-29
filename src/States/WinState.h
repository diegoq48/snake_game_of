#pragma once

#include "State.h"
#include "ofMain.h"

class WinState : public State
{
private:
    ofImage win;

public:
    WinState();
    ~WinState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
};
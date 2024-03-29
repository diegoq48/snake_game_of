#pragma once

#include "State.h"
#include "ofMain.h"

class MenuState : public State
{
private:
    ofImage menu;

public:
    MenuState();
    ~MenuState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
};
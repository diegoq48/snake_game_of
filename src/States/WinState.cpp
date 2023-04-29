#include "WinState.h"

WinState::WinState()
{
}
WinState::~WinState()
{
}

void WinState::reset()
{
    setFinished(false);
    setNextState("");
    return;
}

void WinState::update()
{
}

void WinState::draw()
{
    ofSetColor(ofColor::white);
    win.load("images/win.png");
    win.draw(0, 0, ofGetWidth(), ofGetHeight());
    return;
}

void WinState::keyPressed(int key)
{
    if (key == 'm')
    {
        setFinished(true);
        setNextState("MenuState");
        return;
    }
    else if (key == 'c')
    {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

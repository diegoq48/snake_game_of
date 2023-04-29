#include "pauseState.h"
#include "ofMain.h"

pauseState::pauseState()
{
}
pauseState::~pauseState()
{
}
void pauseState::reset()
{
    setFinished(false);
    setNextState("");
    return;
}
void pauseState::update()
{
}
void pauseState::draw()
{
    ofImage pause;
    ofSetColor(ofColor::white);
    pause.load("images/pause.png");
    pause.draw(0, 0, ofGetWidth(), ofGetHeight());
    return;
}
void pauseState::keyPressed(int key)
{
    if (key == OF_KEY_RETURN)
    {
        setFinished(true);
        setNextState("GameState");
        return;
    }
    else if (key == OF_KEY_ESC)
    {
        setFinished(true);
        std::exit(1);
        return;
    }
    if (key == 'm')
    {
        setFinished(true);
        setNextState("MenuState");
        return;
    }
}

#include "LoseState.h"

LoseState::LoseState()
{
}
LoseState::~LoseState()
{
}

void LoseState::reset()
{
    setFinished(false);
    setNextState("");
    return;
}

void LoseState::update()
{
}

void LoseState::draw()
{

    ofSetColor(ofColor::white);
    gameover.load("images/gameover.png");
    gameover.draw(0, 0, ofGetWidth(), ofGetHeight());
    return;
}
void LoseState::mousePressed(int x, int y, int button)
{
   float dist = ofDist(x, y, ofGetWidth()/2, ofGetHeight()/2);
    if (dist < 1000)
    {
         setFinished(true);
         setNextState("GameState");
         return;
    }
    return;


}

void LoseState::keyPressed(int key)
{
    if (key == 'm')
    {
        setFinished(true);
        setNextState("MenuState");
        return;
    }
    else if (key == 'r')
    {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

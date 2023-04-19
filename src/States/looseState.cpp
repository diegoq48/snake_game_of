#include "looseState.h"


looseState::looseState() {

}   
looseState::~looseState() {

}

void looseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}

void looseState::update() {

}

void looseState::draw() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    // Draw a Rectangle thats void on the inside where it says "Press any key to start"
    ofSetColor(ofColor::white);
    ofDrawBitmapString("You lost", ofGetWidth()/2-8*15/2, ofGetHeight()/2-11);
    ofDrawBitmapString("Press any key to restart.", ofGetWidth()/2-8*15/2, ofGetHeight()/2);
    
}

void looseState::keyPressed(int key) {
    
    setFinished(true);
    setNextState("GameState");
    return;
    
}

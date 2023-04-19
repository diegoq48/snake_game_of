#include "pauseState.h"
#include "ofMain.h"

pauseState::pauseState(){

}
pauseState::~pauseState(){

}
void pauseState::reset(){
    setFinished(false);
    setNextState("");
    return;

}
void pauseState::update(){

}
void pauseState::draw(){
    ofDrawBitmapString("The game is currently paused", ofGetWidth()/2 - 20, ofGetHeight()/2); 
    ofDrawBitmapString("Press the enter key to return to the game or esc to exit the program", ofGetWidth()/2 - 20, ofGetHeight()/2 + 20);
}
void pauseState::keyPressed(int key){
    if(key == OF_KEY_RETURN){
        setFinished(true);
        setNextState("GameState");
        return;
    }
    else if(key == OF_KEY_ESC){
        setFinished(true);
        std::exit(1);
        return;
    }
}

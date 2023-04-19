#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sound.stop();
    sound.load("music/karmaPolice.mp3");
    sound.play();
    sound.setLoop(true);
    sound.setVolume(0.5);
    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    currentState = menuState;

}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            gameState->reset();
            currentState = gameState;
        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;
        }
    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}
//--------------------------------------------------------------
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
    LooseState = new looseState();
    PauseState = new pauseState();
    currentState = menuState;

}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
            if(currentState == PauseState){
                gameState->paused = true;
                std::cout <<"paused" << std::endl;
            }
            gameState->reset();
            currentState = gameState;
            gameState->paused = false;

        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;
        }
        else if(currentState->getNextState() == "looseState"){
            LooseState->reset();
            currentState = LooseState;

        }
        else if(currentState->getNextState() == "pauseState"){
            PauseState->reset();
            currentState = PauseState;
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
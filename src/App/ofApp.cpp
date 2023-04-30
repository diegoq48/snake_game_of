#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    sound.stop();
    sound.load("music/karmaPolice.mp3");
    sound.play();
    sound.setLoop(true);
    sound.setVolume(0.5);
    ofSetWindowTitle("Snake");
    ofSetFrameRate(60);

    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState();
    winState = new WinState();
    PauseState = new pauseState();
    currentState = menuState;
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (currentState->hasFinished())
    {
        if (currentState->getNextState() == "GameState")
        {
            if (currentState == PauseState)
            {
                gameState->paused = true;
                std::cout << "paused" << std::endl;
            }
            gameState->reset();
            currentState = gameState;
            gameState->paused = false;
        }
        else if (currentState->getNextState() == "MenuState")
        {
            gameState->paused = false;
            menuState->reset();
            currentState = menuState;
        }
        else if (currentState->getNextState() == "LoseState")
        {
            loseState->reset();
            currentState = loseState;
        }
        else if (currentState->getNextState() == "WinState")
        {
            gameState->paused = true;
            winState->reset();
            currentState = winState;
        }
        else if (currentState->getNextState() == "pauseState")
        {
            PauseState->reset();
            currentState = PauseState;
        }
    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    currentState->keyPressed(key);
}

//--------------------------------------------------------------
#include "application.h"

#include <iostream>

using namespace std;

Application::Application(){
    currentScreen = NULL;
    graphics = new Graphics();
}

Application::~Application(){
    delete graphics;
}

void Application::pushScreen(Screen* s){
    if(screens.size()>0)
        screens.pop_back();
    screens.push_back(s);
    currentScreen = s;
}

void Application::popScreen(){
    if(screens.size()>0)
        screens.pop_back();
    if(screens.size()>0)
    currentScreen = screens.at(screens.size()-1);
}

void Application::initializeGL(){}

void Application::loadTexture(string path, string name){
    graphics->loadTexture(path,name);
}

void Application::onTick(float secSincePrev){
    //delegate updates to the current screen
    currentScreen->onTick(secSincePrev);
}

void Application::render(){
    currentScreen->render(graphics);
}

void Application::onMouseMoved(QMouseEvent *event, Vector2 windowSize){
    currentScreen->onMouseMoved(event, windowSize);
}

void Application::onKeyPressed(QKeyEvent *event){
    currentScreen->onKeyPressed(event);
}

void Application::onKeyReleased(QKeyEvent *event){
    currentScreen->onKeyReleased(event);
}

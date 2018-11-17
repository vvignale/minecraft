#include "screen.h"
#include <iostream>

using namespace std;

Screen::Screen(){}

Screen::Screen(View* v, Application* a){
    app = a;
    viewer = v;
}

Screen::~Screen(){
    delete app;
    delete viewer;
}

void Screen::setFogUniform(Vector3 pos){
    viewer->setFogState(pos);
}

void Screen::onTick(float secSincePrev){}

void Screen::render(Graphics* g){}

void Screen::onMouseMoved(QMouseEvent *event, Vector2 windowSize){}

void Screen::onKeyPressed(QKeyEvent *event){}

void Screen::onKeyReleased(QKeyEvent *event){}

void Screen::onMousePressed(QMouseEvent *event){}

void Screen::onMouseReleased(QMouseEvent *event){}

void Screen::onMouseDragged(QMouseEvent *event){}

void Screen::onMouseWheeled(QMouseEvent *event){}

void Screen::onResize(){}

void Screen::renderText(string text, Vector2 offsetFromCenter){}

void Screen::endGame(string message){}

#include "minecraftgamescreen.h"


MinecraftGameScreen::MinecraftGameScreen(View* v, Application* app)
    : Screen(v,app)
{
    world = new MinecraftWorld(this);
    //load texture atlas
    app->loadTexture(":/images/terrain.png", "terrain");

    //skybox
    app->loadTexture(":/images/negxSunset.png", "negx");
    app->loadTexture(":/images/negySunset.png", "negy");
    app->loadTexture(":/images/negzSunset.png", "negz");
    app->loadTexture(":/images/posxSunset.png", "posx");
    app->loadTexture(":/images/posySunset.png", "posy");
    app->loadTexture(":/images/poszSunset.png", "posz");
}

 MinecraftGameScreen::~MinecraftGameScreen(){
    delete world;
 }

void MinecraftGameScreen::onTick(float secSincePrev){
    world->onTick(secSincePrev);
}

void MinecraftGameScreen::render(Graphics* g){
    //retrieve eye position (of camera) and then send back to view to set fog uniform
    world->render(g);
}

void MinecraftGameScreen::onMouseMoved(QMouseEvent *event, Vector2 windowSize){
    world->onMouseMoved(event,windowSize);
}

void MinecraftGameScreen::onKeyPressed(QKeyEvent *event){
    world->onKeyPressed(event);
}

void MinecraftGameScreen::onKeyReleased(QKeyEvent *event){
    world->onKeyReleased(event);
}

void MinecraftGameScreen::endGame(string message){
    app->popScreen();
    app->pushScreen(new MinecraftEndScreen(viewer, app, message));
}

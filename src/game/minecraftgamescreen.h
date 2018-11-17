#ifndef MINECRAFTGAMESCREEN_H
#define MINECRAFTGAMESCREEN_H

#include "common_engine/screen.h"
#include "minecraftworld.h"
#include "common_engine/application.h"
#include "minecraftendscreen.h"

class MinecraftGameScreen : public Screen
{
public:
    MinecraftGameScreen(View* v, Application* app);
    ~MinecraftGameScreen();

    void onTick(float secSincePrev);
    void render(Graphics* g);
    void onMouseMoved(QMouseEvent *event, Vector2 windowSize);
    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);

    void endGame(string message);

    //void renderText(string text, Vector2 offsetFromCenter);

private:
    MinecraftWorld* world;
};

#endif // MINECRAFTGAMESCREEN_H

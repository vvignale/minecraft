#ifndef MINECRAFTENDSCREEN_H
#define MINECRAFTENDSCREEN_H
#include "common_engine/graphics.h"
#include "minecraftgamescreen.h"
#include "common_engine/screen.h"
#include "view.h"

class MinecraftEndScreen : public Screen
{
public:
    MinecraftEndScreen(View* v, Application* a, string m);
    void render(Graphics* g);
    void onKeyPressed(QKeyEvent *event);

private:
    string message;
};

#endif // MINECRAFTENDSCREEN_H

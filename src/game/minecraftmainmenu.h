#ifndef MINECRAFTMAINMENU_H
#define MINECRAFTMAINMENU_H

#include "common_engine/screen.h"
#include "view.h"

class MinecraftMainMenu : public Screen
{
public:
    MinecraftMainMenu(View* v, Application* app);
    void render(Graphics* g);
    void onKeyPressed(QKeyEvent *event);

};

#endif // MINECRAFTMAINMENU_H

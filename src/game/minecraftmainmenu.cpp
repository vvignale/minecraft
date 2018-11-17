#include "minecraftmainmenu.h"
#include "minecraftgamescreen.h"

MinecraftMainMenu::MinecraftMainMenu(View* v, Application* app)
    : Screen(v,app)
{
}

void MinecraftMainMenu::render(Graphics* g){
    viewer->renderString("Press n to start a new game");
}

void MinecraftMainMenu::onKeyPressed(QKeyEvent *event){
    if(event->key()==78){
        app->popScreen();
        app->pushScreen(new MinecraftGameScreen(viewer,app));
    }
}

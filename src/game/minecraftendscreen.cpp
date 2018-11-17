#include "minecraftendscreen.h"

MinecraftEndScreen::MinecraftEndScreen(View* v, Application* a, string m)
    : Screen(v, a)
{
    message = m;
}


void MinecraftEndScreen::render(Graphics* g){
    viewer->renderString(message);
}

void MinecraftEndScreen::onKeyPressed(QKeyEvent *event){
    if(event->key()==Qt::Key_N){
        app->popScreen();
        app->pushScreen(new MinecraftGameScreen(viewer,app));
    }
}

#ifndef APPLICATION_H
#define APPLICATION_H

#include "screen.h"
#include "vector.h"
#include "graphics.h"
#include <QKeyEvent>
#include <deque>

//outermost game shell
class Screen;

class Application
{
public:
    Application();
    ~Application();
    std::deque<Screen*> screens;
    void pushScreen(Screen* s);
    void popScreen();

    void onTick(float secSincePrev);
    void render();
    void onResize();

    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);

    void onMousePressed();
    void onMouseReleased();
    void onMouseDragged();
    void onMouseWheeled();
    void onMouseMoved(QMouseEvent *event, Vector2 windowSize);

    virtual void initializeGL();

    void loadTexture(string path, string name);

private:
    Screen* currentScreen;
    Graphics* graphics;


};

#endif // APPLICATION_H

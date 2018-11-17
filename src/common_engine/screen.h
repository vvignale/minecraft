#ifndef SCREEN_H
#define SCREEN_H

#include "graphics.h"
#include "vector.h"
#include <QKeyEvent>

class Application;
class View;
#include "view.h"

class Screen
{

public:
    Screen();
    Screen(View* v, Application* a);
    ~Screen();

    virtual void onTick(float secSincePrev);
    virtual void render(Graphics* g);
    virtual void onResize();

    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);

    virtual void onMousePressed(QMouseEvent *event);
    virtual void onMouseReleased(QMouseEvent *event);
    virtual void onMouseDragged(QMouseEvent *event);
    virtual void onMouseWheeled(QMouseEvent *event);
    virtual void onMouseMoved(QMouseEvent *event, Vector2 windowSize);

    virtual void renderText(string text, Vector2 offsetFromCenter);
    virtual void endGame(string message);
    void setFogUniform(Vector3 pos);

protected:
   Application* app;
   View* viewer;


};

#endif // SCREEN_H

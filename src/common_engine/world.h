#ifndef WORLD_H
#define WORLD_H

#include <QKeyEvent>
#include <list>
#include <QList>
#include "screen.h"

class Entity;
#include "entity.h"

class World
{
public:
    World(Screen* c);
    ~World();

    virtual void onTick(float secSincePrev);
    virtual void render(Graphics* g);
    virtual void addEntity(Entity* e);
    virtual void removeEntity(Entity* e);
    virtual void collideEntities();

    virtual void onMouseMoved(QMouseEvent *event, Vector2 windowSize);
    virtual void onKeyPressed(QKeyEvent *event);
    virtual void onKeyReleased(QKeyEvent *event);

    QList<Entity*> getEntities();

protected:
    QList<Entity*> entities;
    Screen* container;

};

#endif // WORLD_H

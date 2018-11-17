#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"
#include "shape.h"
#include "graphics.h"

class World;
#include "world.h"

class Entity
{
public:
    Entity(Vector3 pos, Vector3 dim, World* w);
    ~Entity();
    virtual void onTick(float secSincePrev);
    virtual void render(Graphics* g);
    virtual Shape* getCollisionShape();
    void updatePosition(Vector3 delta);
    virtual void setPosition(Vector3 newPos);
    Vector3 getPosition();
    Vector3 getVelocity();
    Vector3 getDim();
    void setVisible(bool v);
    void setVelocity(Vector3 vel);
    virtual void onCollide(Entity* e, Vector3 mtv);

protected:
    Vector3 position, dimensions;
    Shape* visualization;
    Shape* collisionShape;      // usually same as visualization but not always
    World* world;

    Vector3 velocity, acceleration, goalVelocity;
    float gravity = -9.8;
    bool visible;

};

#endif // ENTITY_H

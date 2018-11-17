#ifndef WALL_H
#define WALL_H

#include "staticphysicsentity.h"

class Wall : public StaticPhysicsEntity
{
public:
    Wall(Vector3 pos, Vector3 dim, Vector3 n);
    void render(Graphics *g);

protected:
    Vector3 normal;
};

#endif // WALL_H

#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include "entity.h"

class PhysicsEntity : public Entity
{
public:
    PhysicsEntity(Vector3 pos, Vector3 dim, World* w);
    void setGoalVelocity(Vector3 gv);
    void onCollide(Entity *e, Vector3 mtv);
    void onTick(float secSincePrev);

};

#endif // PHYSICSENTITY_H

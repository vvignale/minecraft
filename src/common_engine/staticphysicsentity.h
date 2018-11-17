#ifndef STATICPHYSICSENTITY_H
#define STATICPHYSICSENTITY_H

#include "physicsentity.h"

class StaticPhysicsEntity : public PhysicsEntity
{
public:
    StaticPhysicsEntity(Vector3 pos, Vector3 dim, World* w);
    void onCollide(Entity* e, Vector3 mtv);
    void onTick(float secSincePrev);
};

#endif // STATICPHYSICSENTITY_H

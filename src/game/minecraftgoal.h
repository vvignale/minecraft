#ifndef MINECRAFTGOAL_H
#define MINECRAFTGOAL_H

#include "common_engine/physicsentity.h"
class MinecraftWorld;
#include "minecraftworld.h"
#include "common_engine/aab.h"
#include "common_engine/cylinder.h"

class MinecraftGoal : public PhysicsEntity
{
public:
    MinecraftGoal(Vector3 pos, Vector3 dim, MinecraftWorld* w);
    void onCollide(Entity* e, Vector3 mtv);
    void onTick(float secSincePrev);
};

#endif // MINECRAFTGOAL_H

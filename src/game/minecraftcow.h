#ifndef MINECRAFTCOW_H
#define MINECRAFTCOW_H
#include "common_engine/physicsentity.h"
#include "common_engine/aab.h"
#include "common_engine/cylinder.h"

class MinecraftWorld;
#include "minecraftworld.h"

class MinecraftCow : public PhysicsEntity
{
public:
    MinecraftCow(Vector3 pos, Vector3 dim, World* w, Vector3 axis, float m);
    ~MinecraftCow();
    void onTick(float secSincePrev);
    void onCollide(Entity* e, Vector3 mtv);

private:
    Vector3 moveDir;
    Vector3 startPos;
    float offset;
    float max;
};

#endif // MINECRAFTCOW_H

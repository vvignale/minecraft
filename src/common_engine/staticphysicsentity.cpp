#include "staticphysicsentity.h"

StaticPhysicsEntity::StaticPhysicsEntity(Vector3 pos, Vector3 dim, World* w)
    : PhysicsEntity(pos,dim, w)
{
    velocity = Vector3(0,0,0);
    acceleration = Vector3(0,0,0);
    goalVelocity = Vector3(0,0,0);
}


void StaticPhysicsEntity::onCollide(Entity* e, Vector3 mtv){
    //call back to the other entity to move
    //e->onCollide(this, -mtv);
 }

void StaticPhysicsEntity::onTick(float secSincePrev){}

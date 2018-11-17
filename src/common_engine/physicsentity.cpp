#include "physicsentity.h"

PhysicsEntity::PhysicsEntity(Vector3 pos, Vector3 dim, World* w)
    : Entity(pos, dim, w)
{
}

void PhysicsEntity::setGoalVelocity(Vector3 gv){
    goalVelocity = gv;
}

void PhysicsEntity::onCollide(Entity* e, Vector3 mtv){
    //translate out of collision
    this->updatePosition(mtv/2);
    if(position.y<0){
        this->updatePosition(Vector3(0,-position.y,0));
    }
    //engine side impulse eventually
 }

void PhysicsEntity::onTick(float secSincePrev){
    //xz update
    acceleration = .5*(goalVelocity-Vector3(velocity.x,0,velocity.z));
    //acceleration = goalVelocity;
    velocity += acceleration*secSincePrev;
    //velocity = goalVelocity;

    //y update
    velocity.y += gravity*secSincePrev;
    if(fabs(velocity.x) < 0.01) velocity.x = 0;
    if(fabs(velocity.z) < 0.01) velocity.z = 0;

}


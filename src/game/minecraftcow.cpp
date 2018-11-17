#include "minecraftcow.h"
#include <iostream>

using namespace std;

MinecraftCow::MinecraftCow(Vector3 pos, Vector3 dim, World* w, Vector3 axis, float m)
    : PhysicsEntity(pos,dim, w)
{
    velocity.y = 0;
    QList<Vector2> coords;
    coords.append(Vector2(6,6));
    coords.append(Vector2(7,10));
    coords.append(Vector2(7,7));
    coords.append(Vector2(7,7));
    coords.append(Vector2(7,9));
    coords.append(Vector2(7,8));

    visualization = new AAB(pos, dim.x, Vector3(-1,0,0),coords,"terrain");
    collisionShape = new Cylinder(pos, dim.x*.6, 1, Vector3(1,1,1));

    max = m;
    startPos = Vector3(pos.x,.5,pos.z);
    moveDir = axis;
    offset = 0;
}

MinecraftCow::~MinecraftCow()
{
}

void MinecraftCow::onTick(float secSincePrev){

    PhysicsEntity::onTick(secSincePrev);
    if(position.y<=.51){
        // have the cow move along its axes
        offset += secSincePrev*5;

        this->setPosition(startPos+ moveDir*offset);
        if(offset>max)
            offset = 0;
    }
}

void MinecraftCow::onCollide(Entity* e, Vector3 mtv){
    Entity::onCollide(e,mtv);
    (dynamic_cast<MinecraftWorld*>(world))->endGame();
}







#include "minecraftgoal.h"
#include "iostream"

using namespace std;

MinecraftGoal::MinecraftGoal(Vector3 pos, Vector3 dim, MinecraftWorld* w)
    : PhysicsEntity(pos,dim,w)
{
    velocity.y = 0;
    QList<Vector2> coords;
    coords.append(Vector2(3,7));
    coords.append(Vector2(1,7));
    coords.append(Vector2(2,7));
    coords.append(Vector2(2,7));
    coords.append(Vector2(2,7));
    coords.append(Vector2(2,7));

    visualization = new AAB(pos, dim.x, Vector3(-1,0,0),coords,"terrain");
    collisionShape = new Cylinder(pos, dim.x*.6, 1, Vector3(1,1,1));

}

void MinecraftGoal::onCollide(Entity* e, Vector3 mtv){
    // increase player score and disappear visualization
    if(visible)
        dynamic_cast<MinecraftWorld*>(world)->increaseScore();
    visible = false;
}

void MinecraftGoal::onTick(float secSincePrev){

    PhysicsEntity::onTick(secSincePrev);
//    cout<<"position: "<<position.y<<endl;
    this->setPosition(Vector3(position.x,.5,position.z));
}

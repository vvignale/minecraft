#include "player.h"
#include <iostream>

#define eyeLevel 1.2
#define speed 10

using namespace std;

Player::Player(Vector3 pos, Vector3 dim, World* w)
    : PhysicsEntity(pos,dim, w)
{
    camera = new Camera(pos);
    velocity.y = 0;
    QList<Vector2> coords;
    coords.append(Vector2(1,6));
    coords.append(Vector2(3,6));
    for(int i=0; i<4; i++)
        coords.append(Vector2(2,6));
    visualization = new AAB(pos, dim.x, Vector3(0,0,1),coords,"terrain");
    collisionShape = new Cylinder(pos, dim.x*.6, 1, Vector3(1,1,1));
}

Player::~Player()
{
    delete camera;
}

void Player::onTick(float secSincePrev){
    PhysicsEntity::onTick(secSincePrev);
    camera->update(position);       //update camera to follow player
}

void Player::toggleCamera(){
    camera->toggle();
}

void Player::adjustLook(float deltaPitch, float deltaYaw){
    camera->updateCenter(deltaPitch,deltaYaw);
}

void Player::jump(){
    if(velocity.y==0)
        velocity.y = speed;
}


 void Player::moveVertically(int mode){
     if(mode == -1){
         //move player down
         updatePosition(Vector3(0,-1,0));
     }
     else{
         //move player up
         updatePosition(Vector3(0,1,0));
     }
 }

Vector3 Player::getLookDirection(){
    return camera->normalizedLook;
}

Vector3 Player::getEye(){
    return camera->getEye();
}

void Player::move(Direction dir){

    Vector3 look = camera->normalizedLook;
    Vector3 dirToMove;

    switch (dir){
    case FORWARD:
        goalVelocity = Vector3(look.x, 0, look.z)*speed;
        break;
    case BACKWARD:
        goalVelocity = -Vector3(look.x, 0, look.z)*speed;
        break;
    case RIGHT:
        dirToMove = Vector3(-look.z, look.y, look.x)*speed;
        goalVelocity = Vector3(dirToMove.x, 0, dirToMove.z);
        break;
    case LEFT:
        dirToMove = Vector3(look.z, look.y, -look.x)*speed;
        goalVelocity = Vector3(dirToMove.x, 0, dirToMove.z);
        break;
    }
}

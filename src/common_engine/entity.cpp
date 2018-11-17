#include "entity.h"
#include <iostream>

Entity::Entity(Vector3 pos, Vector3 dim, World* w)
{
    position = pos;
    dimensions = dim;
    world = w;

    velocity = Vector3(0,0,0);
    acceleration = Vector3(0,0,0);
    goalVelocity = Vector3(0,0,0);
    visible = true;
}
Entity::~Entity(){
    delete visualization;
}

void Entity::setVisible(bool v){
    visible = v;
}

void Entity::onTick(float secSincePrev){}

void Entity::render(Graphics* g){
    if(visible)
        visualization->render(g);
//        collisionShape->render(g);

}

Vector3 Entity::getDim(){
    return dimensions;
}

void Entity::updatePosition(Vector3 delta){
    position += delta;
    if(visualization!=NULL)
        visualization->updatePosition(delta);
    if(collisionShape!=NULL)
        collisionShape->updatePosition(delta);
}

Vector3 Entity::getPosition(){
    return position;
}

Vector3 Entity::getVelocity(){
    return velocity;
}

void Entity::setVelocity(Vector3 vel){
     velocity = vel;
 }

void Entity::setPosition(Vector3 newPos){
    position = newPos;
    if(visualization!=NULL)
        visualization->position=newPos;
    if(collisionShape!=NULL)
        collisionShape->position=newPos;
}

Shape* Entity::getCollisionShape(){
    return collisionShape;
}

void Entity::onCollide(Entity* e, Vector3 mtv){}

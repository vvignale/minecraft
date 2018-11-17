#include "world.h"
#include <iostream>

using namespace std;

World::World(Screen* c){
    container = c;
}

World::~World(){
    //loop through and delete all entities in world
    foreach(Entity* e, entities){
        delete e;
    }
}
void World::onTick(float secSincePrev){
    foreach(Entity* e, entities){
        e->onTick(secSincePrev);    //tick all entities
    }

    collideEntities();
}

void World::render(Graphics* g){
    foreach(Entity* e, entities){
        e->render(g);
    }
}

QList<Entity*> World::getEntities(){
    return entities;
}

void World::addEntity(Entity* e){
    entities.push_back(e);
}

void World::removeEntity(Entity* e){
    entities.removeOne(e);
}

void World::collideEntities(){
    //loop through all entities and collide them
    for(int i=0; i<entities.size(); i++){
        for(int j=0; j<entities.size(); j++){
            Entity* original = entities.at(i);
            Entity* other = entities.at(j);
            if(i!=j){
                Vector3 mtv = original->getCollisionShape()->collide(other->getCollisionShape());
                if(!mtv.isZeroVector()){
                    original->onCollide(other, mtv);
                }
            }
        }
    }
}

void World::onMouseMoved(QMouseEvent *event, Vector2 windowSize){}

void World::onKeyPressed(QKeyEvent *event){}

void World::onKeyReleased(QKeyEvent *event){}

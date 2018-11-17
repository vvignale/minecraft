#include "minecraftworld.h"
#include <iostream>
#include <stdio.h>

#define CHUNK_DIM 32
#define WORLD_SIZE 10

using namespace std;

MinecraftWorld::MinecraftWorld(Screen* c)
    : World(c)
{
    player = new Player(Vector3(0,10,5), Vector3(1,1,1),this);
    entities.append(player);

    // a bunch of cows
//    QList<Vector3> startingPos;
//    startingPos.append(Vector3(0,10,-30));
//    startingPos.append(Vector3(60,10,32));
//    startingPos.append(Vector3(-60,10,32));
//    startingPos.append(Vector3(-60,10,-96));
//    startingPos.append(Vector3(60,10,-96));

//    // goal 1
//    foreach(Vector3 goalOnePos, startingPos){

//        entities.append(new MinecraftGoal(goalOnePos, Vector3(1,1,1),this));

//        entities.append(new MinecraftCow(goalOnePos - Vector3(-10,0,10), Vector3(1,1,1),this, Vector3(-1,0,0),20));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(10,0,10), Vector3(1,1,1),this, Vector3(0,0,1),20));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(10,0,-10), Vector3(1,1,1),this, Vector3(1,0,0),20));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(-10,0,-10), Vector3(1,1,1),this, Vector3(0,0,-1),20));

//        entities.append(new MinecraftCow(goalOnePos - Vector3(8,0,8), Vector3(1,1,1),this, Vector3(1,0,0),16));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(8,0,-8), Vector3(1,1,1),this, Vector3(0,0,-1),16));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(-8,0,-8), Vector3(1,1,1),this, Vector3(-1,0,0),16));
//        entities.append(new MinecraftCow(goalOnePos - Vector3(-8,0,8), Vector3(1,1,1),this, Vector3(0,0,1),16));
//    }



    //set up voxel manager
    voxelManager = new MinecraftVoxelManager(player->camera, this);

    //initialize player to be in chunk 0,0 surrounded by 2 chunks on all sides
    playerCurrChunk = Vector3(0,0,0);
    voxelManager->updatePlayerBuffer(playerCurrChunk);

    collision = false;
    score = 0;
}

MinecraftWorld::~MinecraftWorld(){
    //items not in entities
    delete voxelManager;
}

void MinecraftWorld::increaseScore(){
    score += 1;
    if(score == 5)
        container->endGame("You win! Press N to restart.");
}


void MinecraftWorld::endGame(){
    // handle lose
    container->endGame("You lose. Press N to restart");
}

void MinecraftWorld::onMouseMoved(QMouseEvent *event, Vector2 windowSize){
    int deltaX = event->x() - windowSize.x / 2;
    int deltaY = event->y() - windowSize.y / 2;
    player->adjustLook(deltaY,deltaX);
}

void MinecraftWorld::onKeyPressed(QKeyEvent *event){
    //player motion
    //cout << "key button: " << event->key() << endl;
    if(event->key()==87)
        player->move(Player::FORWARD);
    else if(event->key()==83)
        player->move(Player::BACKWARD);
    else if(event->key()==68)
         player->move(Player::RIGHT);
    else if(event->key()==65)
         player->move(Player::LEFT);
    else if(event->key()==32)
        player->jump();
    else if(event->key()==Qt::Key_Q)
        voxelManager->removeBlock(result.first);
    else if(event->key()==Qt::Key_E)
        voxelManager->addBlock(result); //add block to world
    else if(event->key()==Qt::Key_C)
        creationMode = !creationMode;
}



//get nearest intersected face/block and add or remove depending on mode
void MinecraftWorld::raycastEnvironment(){

    collision = true;
    //call for the voxel manager to return closest block raycasted given a ray
    int xSign = 1, zSign = 1;
    Vector3 startingPos;

    startingPos = player->getEye() + Vector3(xSign*.5,0.,zSign*.5);

    result = voxelManager->raycastEnvironment(Ray(startingPos, player->getLookDirection()));
    if(result.second==Voxel::none)
        collision=false;
}

void MinecraftWorld::onKeyReleased(QKeyEvent *event){

    if(event->key()==87 || event->key()==83 || event->key()==68 || event->key()==65){
        player->setGoalVelocity(Vector3(0,0,0));
    }
    else if(event->key()==80){
        player->toggleCamera();
    }
    else if(event->key()==32)
        player->jump();

}

void MinecraftWorld::onTick(float secSincePrev){

    if(creationMode)
        raycastEnvironment();       // remove to disable creation mode

    World::onTick(secSincePrev);
    voxelManager->onTick(secSincePrev);

    //look up and print out current player chunk
    Chunk* curr = voxelManager->lookUpChunk(player->getPosition());
    if(curr!=NULL){
        Vector3 currPos = curr->getPosition()/CHUNK_DIM;
        if(currPos!=playerCurrChunk){
            playerCurrChunk = currPos;
            //this runs once when we change chunks
            voxelManager->updatePlayerBuffer(playerCurrChunk);
        }
    }

}

void MinecraftWorld::render(Graphics* g){

    glBindTexture(GL_TEXTURE_2D, 0);

    //render skybox. center around player
    g->renderSkybox(player->getPosition());

    World::render(g);
    voxelManager->render(g);

    if(collision){
        glColor3f(.5,0,0);
        g->renderVoxelFace(result.second, result.first);
    }
}

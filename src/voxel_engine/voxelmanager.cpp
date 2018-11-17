#include "voxelmanager.h"
#include <iostream>
#include <cmath>
#define EPSILON .01
#define CHUNK_DIM 32
using namespace std;

VoxelManager::VoxelManager(Camera* cam, World* w)
{
    voxelTypes = map<char, Voxel*>();
//    chunks.clear();
    camera = cam;
    world = w;
    entities = world->getEntities();
//    noiseGenerator = new NoiseGenerator();
    noiseGenerator = new PerlinNoise(.2, .1, .5, 2, 12);

    toAdd.clear();
    chunksOnScreen.clear();
    justLoaded = false;
}

VoxelManager::~VoxelManager(){
    delete noiseGenerator;
}

int VoxelManager::getNumChunks(){
    return chunksOnScreen.size();
}

void VoxelManager::addChunk(Chunk* c){
    //chunks.insert(make_pair(key, value));
    //put the chunk in the toAdd list. will be dequeued, built, and put in onScreen list during ticks
    toAdd.enqueue(c);
}

Voxel* VoxelManager::getVoxelFromType(char c){
    return voxelTypes.at(c);
}

Chunk* VoxelManager::lookUpChunk(Vector3 position){

    QHash<int, Chunk*>::iterator it;
    for(it=chunksOnScreen.begin(); it!=chunksOnScreen.end(); ++it){
        //chunk position
        Vector3 chunkPos = it.value()->getPosition();

        if(position.x<chunkPos.x+32 && position.x>=chunkPos.x){
            if(position.y<chunkPos.y+32 && position.y>=chunkPos.y){
                if(position.z<chunkPos.z+32 && position.z>=chunkPos.z){
                    //if all these conditions met, the position is in the chunk
                    return  it.value();
                }
            }
        }
    }
    return NULL;        //off the edge of the world
}


float VoxelManager::getCollisionsY(Entity* e, Vector3 finalPos, int yDir){

    float yStartF = e->getPosition().y;
    yStartF += yDir * e->getDim().y/2.;

    float yEndF = finalPos.y;
    yEndF += yDir * e->getDim().y/2.;

    int yStart, yEnd;

    if(yDir<0){
        yStart = floor(yStartF);    //add dir?
    }
    else
        yStart = ceil(yStartF) + yDir;

    yEnd = floor(yEndF);

    int xStart = floor(e->getPosition().x - e->getDim().x/2.);
    int xEnd = floor(e->getPosition().x + e->getDim().x/2.);

    int zStart = floor(e->getPosition().z - e->getDim().z/2.);
    int zEnd = floor(e->getPosition().z + e->getDim().z/2.);

    float eps = .001;

    for( int y = yStart; yDir>0?(y<=yEnd):(y>=yEnd); y+= yDir){

        for(int x=xStart; x<=xEnd; x++){
            for(int z=zStart; z<=zEnd; z++){

                Vector3 pos = Vector3(x,y,z);
                Chunk* lookup = lookUpChunk(pos);
                if(lookup!=NULL){
                    Vector3 relativeCoords = pos - lookup->getPosition();

                    if(!lookup->getVoxel(relativeCoords)->isTransparent()){

                        if(yDir<0)
                            return y + 1 + e->getDim().y/2. + eps;
                        return y - e->getDim().y/2. - eps;
                    }
                }
            }
        }
    }

    return finalPos.y;

}


float VoxelManager::getCollisionsX(Entity* e, Vector3 finalPos, int xDir){

    float xStartF = e->getPosition().x;
    xStartF += xDir * e->getDim().x/2.;

    float xEndF = finalPos.x;
    xEndF += xDir * e->getDim().x/2.;

    int xStart, xEnd;

    if(xDir<0)
        xStart = floor(xStartF);
    else
        xStart = ceil(xStartF);

    xEnd = floor(xEndF);

    int yStart = floor(e->getPosition().y - e->getDim().y/2.);
    int yEnd = floor(e->getPosition().y + e->getDim().y/2.);

    int zStart = floor(e->getPosition().z - e->getDim().z/2.);
    int zEnd = floor(e->getPosition().z + e->getDim().z/2.);

    float eps = .001;

    for( int x = xStart; xDir>0?(x<=xEnd):(x>=xEnd); x+= xDir){

        for(int y=yStart; y<=yEnd; y++){
            for(int z=zStart; z<=zEnd; z++){

                Vector3 pos = Vector3(x,y,z);
                Chunk* lookup = lookUpChunk(pos);
                if(lookup!=NULL){
                    Vector3 relativeCoords = pos - lookup->getPosition();
                    if(!lookup->getVoxel(relativeCoords)->isTransparent()){

                        if(xDir<0)
                            return x + 1 + e->getDim().x/2. + eps;
                        return x - e->getDim().x/2. - eps;
                    }
                }
            }
        }
    }
    return finalPos.x;
}

float VoxelManager::getCollisionsZ(Entity* e, Vector3 finalPos, int zDir){

    float zStartF = e->getPosition().z;
    zStartF += zDir * e->getDim().z/2.;

    float zEndF = finalPos.z;
    zEndF += zDir * e->getDim().z/2.;

    int zStart, zEnd;

    if(zDir<0)
        zStart = floor(zStartF);
    else
        zStart = ceil(zStartF);

    zEnd = floor(zEndF);

    int yStart = floor(e->getPosition().y - e->getDim().y/2.);
    int yEnd = floor(e->getPosition().y + e->getDim().y/2.);

    int xStart = floor(e->getPosition().x - e->getDim().x/2.);
    int xEnd = floor(e->getPosition().x + e->getDim().x/2.);

    float eps = .001;

    for( int z = zStart; zDir>0?(z<=zEnd):(z>=zEnd); z+= zDir){

        for(int y=yStart; y<=yEnd; y++){
            for(int x=xStart; x<=xEnd; x++){

                Vector3 pos = Vector3(x,y,z);
                Chunk* lookup = lookUpChunk(pos);
                if(lookup!=NULL){
                    Vector3 relativeCoords = pos - lookup->getPosition();
                    if(!lookup->getVoxel(relativeCoords)->isTransparent()){

                        if(zDir<0)
                            return z + 1 + e->getDim().z/2. + eps;
                        return z - e->getDim().z/2. - eps;
                    }
                }
            }
        }
    }
    return finalPos.z;

}


void VoxelManager::sweepTest(Entity* e, float time){

    // y sweep

    Vector3 currPos = e->getPosition();
    Vector3 currVel = e->getVelocity();
    Vector3 projectedPos = currPos + currVel*time;

    Vector3 finalPos = projectedPos;
    Vector3 finalVel = currVel;

    int xDir,yDir,zDir;

    xDir = 0;
    if(currVel.x>0)
        xDir = 1;
    else if(currVel.x<0)
        xDir = -1;

    if(xDir != 0){

        float xPos = getCollisionsX(e, finalPos, xDir);

        finalPos.x = xPos;
        if(xPos != projectedPos.x)
            finalVel.x = 0.0;
    }

    zDir = 0;
    if(currVel.z>0)
        zDir = 1;
    else if(currVel.z<0)
        zDir = -1;

    if(zDir != 0){

        float zPos = getCollisionsZ(e, finalPos, zDir);

        finalPos.z = zPos;
        if(zPos != projectedPos.z)
            finalVel.z = 0.0;
    }

    e->setPosition(finalPos);
    e->setVelocity(finalVel);


    yDir = 0;
    if(currVel.y>0)
        yDir = 1;
    else if(currVel.y<0)
        yDir = -1;

    if(yDir != 0) {
        float yPos = getCollisionsY(e, finalPos, yDir);

        finalPos.y = yPos;
        if(yPos != projectedPos.y)
            finalVel.y = 0.0;

    }

    e->setPosition(finalPos);
    e->setVelocity(finalVel);

}

//fast grid based raycasting of environment
QPair<Vector3, Voxel::face> VoxelManager::raycastEnvironment(Ray ray){

    QPair<Vector3,Voxel::face> toRet;

//    cout<<"starting position: "<<ray.origin<<endl;
//    cout<<"direction: "<<ray.direction<<endl;

    int stepX,stepY,stepZ;
    float tDeltaX,tDeltaY,tDeltaZ;
    int X,Y,Z;
    float tMaxX,tMaxY,tMaxZ;

    cout << "orign: " << ray.origin << endl;

    cout << "dir: " << ray.direction << endl;

    //XYZ start out as the integer block coordinates of the player
    //get this by flooring the player's position (ie the ray origin)
    X = floor(ray.origin.x);//+.5;
    Y = floor(ray.origin.y);//+.5;
    Z = floor(ray.origin.z);//+.5;

    //step is determined by the direction that the ray is moving
    //deal with special case axis aligned rays
    if(ray.direction.x>0)
        stepX = 1;
    else if(ray.direction.x<0)
        stepX = -1;
    else if(ray.direction.x==0)
        stepX = 0;
    if(ray.direction.y>0)
        stepY = 1;
    else if(ray.direction.y<0)
        stepY = -1;
    else if(ray.direction.y==0)
        stepY = 0;
    if(ray.direction.z>0)
        stepZ = 1;
    else if(ray.direction.z<0)
        stepZ = -1;
    else if(ray.direction.z==0)
        stepZ = 0;

    //tMax is the t val to get to next integer bounday
    if(ray.direction.x!=0)
        tMaxX = (ceil(ray.origin.x) - ray.origin.x)/fabs(ray.direction.x);
        //tMaxX = fabs((ceil(ray.origin.x) - ray.origin.x)/fabs(ray.direction.x));

    else
        tMaxX = FLT_MAX;    //essentially there is no t value that will get you to the next boundary because you can't move there

    if(ray.direction.y!=0)
        tMaxY = (ceil(ray.origin.y) - ray.origin.y)/fabs(ray.direction.y);
        //tMaxY = fabs((ceil(ray.origin.y) - ray.origin.y)/fabs(ray.direction.y));

    else
        tMaxY =  FLT_MAX;

    if(ray.direction.z!=0)
        tMaxZ = (ceil(ray.origin.z) - ray.origin.z)/fabs(ray.direction.z);
        //tMaxZ = fabs((ceil(ray.origin.z) - ray.origin.z)/fabs(ray.direction.z));

    else
        tMaxZ = FLT_MAX;

    //tDelta is step divided by direction for each. t value to span a unit of step
    //no need to bother with special case here because will never use the t delta values in 0 directions
    tDeltaX = fabs(stepX/ray.direction.x);
    tDeltaY = fabs(stepY/ray.direction.y);
    tDeltaZ = fabs(stepZ/ray.direction.z);

    Voxel::face faceHit;        //will be set by whichever direction is last updated

    //loop:
    while(true){

        //process step

//        cout<<"block processing: "<<Vector3(X,Y,Z)<<endl;

        //look up chunk and voxel at location and if it's not transparent deal with it
        Chunk* currChunk = lookUpChunk(Vector3(X,Y,Z));

        if(currChunk==NULL){
            toRet.second = Voxel::none;      //went off the world, error condition
            return toRet;
        }

        //look up voxel within chunk
        Vector3 relativePos = Vector3(X,Y,Z)-currChunk->getPosition();
        Voxel* currVox = currChunk->getVoxel(relativePos);

        //check what kind of voxel it is. if not a space voxel, register a hit and deal
        if(currVox->getType() != 'n'){
            toRet.first = Vector3(X,Y,Z);// + Vector3(0,0,0);
            toRet.second = faceHit;
            return toRet;
        }

        //update step
        if(tMaxX < tMaxY){
            if(tMaxX < tMaxZ){
                X += stepX;
                tMaxX += tDeltaX;
                if(stepX==1)
                    faceHit = Voxel::back;
                else
                    faceHit = Voxel::front;
            }
            else{
                Z += stepZ;
                tMaxZ += tDeltaZ;
                if(stepZ==1)
                    faceHit = Voxel::left;
                else
                    faceHit = Voxel::right;
            }
        }
        else{
            if(tMaxY < tMaxZ){
                Y += stepY;
                tMaxY += tDeltaY;
                if(stepY==1)
                    faceHit = Voxel::bottom;
                else
                    faceHit = Voxel::top;
            }
            else{
                Z += stepZ;
                tMaxZ += tDeltaZ;
                if(stepZ==1)
                    faceHit = Voxel::left;
                else
                    faceHit = Voxel::right;
            }
        }

    }

}

void VoxelManager::updatePlayerBuffer(Vector3 playerPos){}

//add block to world that is adjacent to this block in direction of the face
void VoxelManager::addBlock(QPair<Vector3,Voxel::face> adjacentBlock){
    Vector3 worldPosToAdd = adjacentBlock.first;
    //depending on the face of the block we hit, add face normal to adjacent block
    switch(adjacentBlock.second){
        case 0:
            worldPosToAdd += Vector3(0,-1,0);
            break;
        case 1:
            worldPosToAdd += Vector3(0,1,0);
            break;
        case 2:
            worldPosToAdd += Vector3(0,0,1);
            break;
        case 3:
            worldPosToAdd += Vector3(0,0,-1);
            break;
        case 4:
            worldPosToAdd += Vector3(1,0,0);
            break;
        case 5:
            worldPosToAdd += Vector3(-1,0,0);
            break;
        default:
            break;
    }

    if(worldPosToAdd!=adjacentBlock.first){     //if have a valid point to add a block to
        //look up the chunk this is in
        Chunk* locatedChunk = lookUpChunk(worldPosToAdd);
        if(locatedChunk!=NULL){
            //get the exact block and change its id and rebuild
            Vector3 relativePos = worldPosToAdd-locatedChunk->getPosition();
            int indexToSet = relativePos.x*CHUNK_DIM*CHUNK_DIM + relativePos.z*CHUNK_DIM + relativePos.y;
            locatedChunk->blocks[indexToSet].c = 'g';
            locatedChunk->resetVBO();
        }
    }
}

//look up and remove the block at the given location (can only be done to paged in, visible blocks)
void VoxelManager::removeBlock(Vector3 position){

    Chunk* containingChunk = lookUpChunk(position);
    if(containingChunk!=NULL){
        Vector3 relativePos = position-containingChunk->getPosition();
        Voxel* vox = containingChunk->getVoxel(relativePos);

        if(!vox->isTransparent()){
            //block is removable, set it to transparent and then rebuild vbo for this chunk
            int indexToSet = relativePos.x*CHUNK_DIM*CHUNK_DIM + relativePos.z*CHUNK_DIM + relativePos.y;
            containingChunk->blocks[indexToSet].c = 'n';
            containingChunk->resetVBO();
        }
    }
}

void VoxelManager::onTick(float secSincePrev){

    if(!toAdd.isEmpty() && !justLoaded){
        Chunk* add = toAdd.dequeue();
        Vector3 addPos = add->getPosition();
        int index = addPos.x*CHUNK_DIM*CHUNK_DIM + addPos.z*CHUNK_DIM + addPos.y;

        // check that not already on screen before adding
        if(!chunksOnScreen.contains(index)){
            add->resetVBO();
            chunksOnScreen.insert(index, add);
            justLoaded = true;
        }
    }
    else
        justLoaded = false;

    //regular collisions in world
    foreach(Entity* e, entities){
        sweepTest(e, secSincePrev);
    }
}

void VoxelManager::render(Graphics* g){

    QHash<int, Chunk*>::iterator it;
    for(it=chunksOnScreen.begin(); it!=chunksOnScreen.end(); ++it){
        if(camera->isInView(it.value())){   //frustum culling
            it.value()->render(g);
        }
    }

    for(it=chunksOnScreen.begin(); it!=chunksOnScreen.end(); ++it){
        if(camera->isInView(it.value())){
            it.value()->renderWater(g);
        }
    }

    for(it=chunksOnScreen.begin(); it!=chunksOnScreen.end(); ++it){
        if(camera->isInView(it.value())){
            it.value()->renderTransparent(g);
        }
    }

}

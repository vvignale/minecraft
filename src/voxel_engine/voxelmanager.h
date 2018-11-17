#ifndef VOXELMANAGER_H
#define VOXELMANAGER_H

#include <map>
#include <QList>
#include "common_engine/graphics.h"
#include "voxel.h"
#include "common_engine/world.h"
#include "common_engine/ray.h"

class Chunk;
class Camera;
#include "common_engine/camera.h"
#include "chunk.h"
#include <QQueue>
#include <QHash>
#include "common_engine/noisegenerator.h"
#include "common_engine/perlinnoise.h"
#include "float.h"

class VoxelManager
{
public:
    VoxelManager(Camera* cam, World* w);
    ~VoxelManager();
    void addChunk(Chunk* c);
    void render(Graphics* g);
    Voxel* getVoxelFromType(char c);
    int getNumChunks();
    void onTick(float secSincePrev);

    void addBlock(QPair<Vector3,Voxel::face> adjacentBlock);
    void removeBlock(Vector3 position);

    QPair<Vector3, Voxel::face> raycastEnvironment(Ray ray);
    void sweepTest(Entity* e, float time);
    Chunk* lookUpChunk(Vector3 position);                   //given a world position, look up which chunk it's in

    float getCollisionsY(Entity* e, Vector3 finalPos, int yDir);
    float getCollisionsX(Entity* e, Vector3 finalPos, int xDir);
    float getCollisionsZ(Entity* e, Vector3 finalPos, int zDir);

     virtual void updatePlayerBuffer(Vector3 playerPos);

protected:
    QHash<int, Chunk*> chunksOnScreen;
    QQueue<Chunk*> toAdd;

    map<char, Voxel*> voxelTypes;
    Camera* camera;                                         //used for frustum culling
    World* world;
    QList<Entity*> entities;
//    NoiseGenerator* noiseGenerator;
    PerlinNoise* noiseGenerator;

    bool justLoaded;

};

#endif // VOXELMANAGER_H


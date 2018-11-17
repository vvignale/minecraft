#ifndef MINECRAFTCHUNK_H
#define MINECRAFTCHUNK_H

#include "voxel_engine/chunk.h"

class MinecraftWorld;
#include "minecraftworld.h"
#include "minecraftvoxelmanager.h"


class MinecraftChunk : public Chunk
{
public:
//    MinecraftChunk(int dim, MinecraftWorld* w, MinecraftVoxelManager* mvm, Vector3 p,NoiseGenerator* ng);
    MinecraftChunk(int dim, MinecraftWorld* w, MinecraftVoxelManager* mvm, Vector3 p,PerlinNoise* ng);
    void resetVBO();

private:
    MinecraftWorld* world;
};

#endif // MINECRAFTCHUNK_H

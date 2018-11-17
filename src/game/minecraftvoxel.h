#ifndef MINECRAFTVOXEL_H
#define MINECRAFTVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftVoxel : Voxel
{
public:
    MinecraftVoxel(int t);
    void render(Graphics* g);
};

#endif // MINECRAFTVOXEL_H

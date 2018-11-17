#ifndef MINECRAFTGRASSVOXEL_H
#define MINECRAFTGRASSVOXEL_H

#include "common_engine/entity.h"
#include "voxel_engine/voxel.h"

class MinecraftGrassVoxel : public Voxel
{
public:
    MinecraftGrassVoxel(bool t, bool p,int div,string tex,char type);
    void render(Graphics* g);
};

#endif // MINECRAFTGRASSVOXEL_H

#ifndef MINECRAFTTALLGRASSVOXEL_H
#define MINECRAFTTALLGRASSVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftTallGrassVoxel : public Voxel
{
public:

    MinecraftTallGrassVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftTallGrassVoxel();
};

#endif // MINECRAFTTALLGRASSVOXEL_H

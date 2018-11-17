#ifndef MINECRAFTICEVOXEL_H
#define MINECRAFTICEVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftIceVoxel : public Voxel
{
public:
    MinecraftIceVoxel(bool t, bool p,int div,string tex,char type);
    void render(Graphics* g);
};

#endif // MINECRAFTICEVOXEL_H

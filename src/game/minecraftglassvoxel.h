#ifndef MINECRAFTGLASSVOXEL_H
#define MINECRAFTGLASSVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftGlassVoxel : public Voxel
{
public:
    MinecraftGlassVoxel(bool t, bool p,int div,string tex,char type);
    void render(Graphics* g);
};

#endif // MINECRAFTGLASSVOXEL_H

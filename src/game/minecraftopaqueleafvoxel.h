#ifndef MINECRAFTOPAQUELEAFVOXEL_H
#define MINECRAFTOPAQUELEAFVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftOpaqueLeafVoxel : public Voxel
{
public:
    MinecraftOpaqueLeafVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftOpaqueLeafVoxel();
};

#endif // MINECRAFTOPAQUELEAFVOXEL_H

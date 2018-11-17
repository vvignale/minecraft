#ifndef MINECRAFTWATERVOXEL_H
#define MINECRAFTWATERVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftWaterVoxel : public Voxel
{
public:
    MinecraftWaterVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftWaterVoxel();
};

#endif // MINECRAFTWATERVOXEL_H

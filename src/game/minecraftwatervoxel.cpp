#include "minecraftwatervoxel.h"

MinecraftWaterVoxel::MinecraftWaterVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{

    topIndex = Vector2(8,7);
    bottomIndex = Vector2(8,7);
    sideIndex = Vector2(8,7);

}

MinecraftWaterVoxel::~MinecraftWaterVoxel()
{

}


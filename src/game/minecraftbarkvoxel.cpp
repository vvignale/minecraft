#include "minecraftbarkvoxel.h"

MinecraftBarkVoxel::MinecraftBarkVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(5,6);
    bottomIndex = Vector2(5,6);
    sideIndex = Vector2(5,6);
}

MinecraftBarkVoxel::~MinecraftBarkVoxel(){}


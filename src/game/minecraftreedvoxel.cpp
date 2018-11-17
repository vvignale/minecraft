#include "minecraftreedvoxel.h"

MinecraftReedVoxel::MinecraftReedVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
       topIndex = Vector2(1,2);
       bottomIndex = Vector2(1,2);
       sideIndex = Vector2(1,2);
}


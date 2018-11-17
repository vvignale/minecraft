#include "minecraftleafvoxel.h"

MinecraftLeafVoxel::MinecraftLeafVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(3,4);
    bottomIndex = Vector2(3,4);
    sideIndex = Vector2(3,4);
}

MinecraftLeafVoxel::~MinecraftLeafVoxel()
{

}


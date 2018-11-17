#include "minecraftopaqueleafvoxel.h"

MinecraftOpaqueLeafVoxel::MinecraftOpaqueLeafVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(5,8);
    bottomIndex = Vector2(5,8);
    sideIndex = Vector2(5,8);
}

MinecraftOpaqueLeafVoxel::~MinecraftOpaqueLeafVoxel()
{

}


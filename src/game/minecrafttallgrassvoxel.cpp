#include "minecrafttallgrassvoxel.h"

MinecraftTallGrassVoxel:: MinecraftTallGrassVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(0,14);
    bottomIndex = Vector2(0,14);
    sideIndex = Vector2(5,13);
}

MinecraftTallGrassVoxel::~MinecraftTallGrassVoxel()
{

}


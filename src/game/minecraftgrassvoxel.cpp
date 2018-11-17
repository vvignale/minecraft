#include "minecraftgrassvoxel.h"
#include <iostream>

using namespace std;

MinecraftGrassVoxel::MinecraftGrassVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(0,0);
    bottomIndex = Vector2(0,2);
    sideIndex = Vector2(0,3);
}

void MinecraftGrassVoxel::render(Graphics* g){
    //g->renderVoxel("terrain", topIndex, bottomIndex, sideIndex,16);
}

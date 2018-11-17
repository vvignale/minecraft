#include "minecrafticevoxel.h"

#include <iostream>

using namespace std;

MinecraftIceVoxel::MinecraftIceVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(1,6);
    bottomIndex = Vector2(3,6);
    sideIndex = Vector2(2,6);
}

void MinecraftIceVoxel::render(Graphics* g){
    //g->renderVoxel("terrain", topIndex, bottomIndex, sideIndex,16);
}

#include "minecraftglassvoxel.h"

#include <iostream>

using namespace std;

MinecraftGlassVoxel::MinecraftGlassVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(1,8);
    bottomIndex = Vector2(3,8);
    sideIndex = Vector2(2,8);

}

void MinecraftGlassVoxel::render(Graphics* g){
    //g->renderVoxel("terrain", topIndex, bottomIndex, sideIndex,16);
}

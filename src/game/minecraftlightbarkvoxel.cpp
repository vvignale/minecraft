#include "minecraftlightbarkvoxel.h"

minecraftlightbarkvoxel::minecraftlightbarkvoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    topIndex = Vector2(5,7);
    bottomIndex = Vector2(5,7);
    sideIndex = Vector2(5,7);
}

minecraftlightbarkvoxel::~minecraftlightbarkvoxel()
{

}


#ifndef MINECRAFTBARKVOXEL_H
#define MINECRAFTBARKVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftBarkVoxel : public Voxel
{
public:
    MinecraftBarkVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftBarkVoxel();
};

#endif // MINECRAFTBARKVOXEL_H

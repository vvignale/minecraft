#ifndef MINECRAFTFLOWERVOXEL_H
#define MINECRAFTFLOWERVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftFlowerVoxel : public Voxel
{
public:
    MinecraftFlowerVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftFlowerVoxel();
};

#endif // MINECRAFTFLOWERVOXEL_H

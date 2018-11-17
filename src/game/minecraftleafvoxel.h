#ifndef MINECRAFTLEAFVOXEL_H
#define MINECRAFTLEAFVOXEL_H

#include "voxel_engine/voxel.h"

class MinecraftLeafVoxel : public Voxel
{
public:
    MinecraftLeafVoxel(bool t, bool p,int div,string tex,char type);
    ~MinecraftLeafVoxel();
};

#endif // MINECRAFTLEAFVOXEL_H

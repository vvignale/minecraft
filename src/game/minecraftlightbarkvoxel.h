#ifndef MINECRAFTLIGHTBARKVOXEL_H
#define MINECRAFTLIGHTBARKVOXEL_H

#include "voxel_engine/voxel.h"

class minecraftlightbarkvoxel : public Voxel

{
public:
    minecraftlightbarkvoxel(bool t, bool p,int div,string tex,char type);
    ~minecraftlightbarkvoxel();
};

#endif // MINECRAFTLIGHTBARKVOXEL_H

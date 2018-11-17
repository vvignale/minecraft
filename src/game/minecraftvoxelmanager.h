#ifndef MINECRAFTVOXELMANAGER_H
#define MINECRAFTVOXELMANAGER_H

#include "voxel_engine/voxelmanager.h"
#include "minecraftgrassvoxel.h"
#include "minecraftwatervoxel.h"
#include "minecraftglassvoxel.h"
#include "minecraftbarkvoxel.h"
#include "minecraftleafvoxel.h"
#include "minecrafticevoxel.h"
#include "minecraftreedvoxel.h"
#include "minecraftflowervoxel.h"
#include "minecrafttallgrassvoxel.h"
#include "minecraftchunk.h"
#include "minecraftlightbarkvoxel.h"
#include "minecraftopaqueleafvoxel.h"

class MinecraftVoxelManager : public VoxelManager
{
public:
    MinecraftVoxelManager(Camera* cam, MinecraftWorld* w);
    void updatePlayerBuffer(Vector3 playerPos);
};

#endif // MINECRAFTVOXELMANAGER_H

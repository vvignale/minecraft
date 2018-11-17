#ifndef MINECRAFTWORLD_H
#define MINECRAFTWORLD_H

#include "common_engine/world.h"
#include "common_engine/vector.h"
#include "voxel_engine/chunk.h"
#include "voxel_engine/voxel.h"
#include "minecraftgrassvoxel.h"
#include "common_engine/player.h"
#include "common_engine/noisegenerator.h"
#include "minecraftcow.h"
#include "minecraftgoal.h"

class MinecraftChunk;
class MinecraftVoxelManager;
#include "minecraftchunk.h"
#include "minecraftvoxelmanager.h"

class MinecraftWorld : public World
{
public:
    MinecraftWorld(Screen* c);
    ~MinecraftWorld();
    void onTick(float secSincePrev);
    void render(Graphics* g);
    void onMouseMoved(QMouseEvent *event, Vector2 windowSize);
    void onKeyPressed(QKeyEvent *event);
    void onKeyReleased(QKeyEvent *event);
    void raycastEnvironment();
    void increaseScore();
    void endGame();

private:
    MinecraftVoxelManager* voxelManager;
    Player* player;
    Vector3 playerCurrChunk;
    QPair<Vector3,Voxel::face> result;
    bool collision;

    int score;
    bool creationMode = false;

};

#endif // MINECRAFTWORLD_H

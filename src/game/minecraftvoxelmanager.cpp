#include "minecraftvoxelmanager.h"
#define CHUNK_DIM 32


MinecraftVoxelManager::MinecraftVoxelManager(Camera* cam, MinecraftWorld* w)
    : VoxelManager(cam, w)
{
    //set up voxel type map
    voxelTypes.insert(pair<char,Voxel*>('g', new MinecraftGrassVoxel(false,true,16,"terrain",'g')));     //visible grass

    voxelTypes.insert(pair<char,Voxel*>('n', new MinecraftGrassVoxel(true,true,16, "terrain",'n')));     //invisible grass (air)

    voxelTypes.insert(pair<char,Voxel*>('v', new MinecraftGlassVoxel(false,true,16, "terrain",'v')));     //visible glass

    voxelTypes.insert(pair<char,Voxel*>('i', new MinecraftIceVoxel(false,true,16, "terrain",'i')));     //visible ice

    voxelTypes.insert(pair<char,Voxel*>('r', new MinecraftReedVoxel(false,true,16, "terrain",'r')));     //sand

    voxelTypes.insert(pair<char,Voxel*>('b', new MinecraftBarkVoxel(false,true,16, "terrain",'b')));     //bark

    voxelTypes.insert(pair<char,Voxel*>('p', new minecraftlightbarkvoxel(false,true,16, "terrain",'p')));   // light bark (palm bark)

    voxelTypes.insert(pair<char,Voxel*>('l', new MinecraftLeafVoxel(false,true,16, "terrain",'l')));     //leaf

    voxelTypes.insert(pair<char,Voxel*>('o', new MinecraftOpaqueLeafVoxel(false,true,16, "terrain",'o')));     //opaque leaf

    voxelTypes.insert(pair<char,Voxel*>('f', new MinecraftFlowerVoxel(true,true,16, "terrain",'f')));     //flower

    voxelTypes.insert(pair<char,Voxel*>('t', new MinecraftTallGrassVoxel(true,true,16, "terrain",'t')));     //tall grass

    voxelTypes.insert(pair<char,Voxel*>('w', new MinecraftWaterVoxel(true,true,16, "terrain",'w')));     //water
}

//figure out which chunks are in range and add to appropriate lists
void MinecraftVoxelManager::updatePlayerBuffer(Vector3 playerPos){
    //set to a buffer of 2
    Chunk* c1;
    QList<int> positionsOnScreen;
    positionsOnScreen.clear();

    for(int i=playerPos.x-2; i<playerPos.x+3; i++){
        for(int j=playerPos.y-1; j<playerPos.y+2; j++){
            for(int k=playerPos.z-2; k<playerPos.z+3; k++){
                Vector3 pos = CHUNK_DIM*Vector3(i,j,k);
                c1 = new MinecraftChunk(CHUNK_DIM, dynamic_cast<MinecraftWorld*>(world), this, pos,noiseGenerator);

                // only enqueue if position not already on screen
                int key = pos.x*CHUNK_DIM*CHUNK_DIM + pos.z*CHUNK_DIM + pos.y;
                positionsOnScreen.append(key);
                if(!chunksOnScreen.contains(key))
                    addChunk(c1);
            }
        }
    }

    //REMOVAL CODE:
    QList<int> toRemove;
    QHash<int, Chunk*>::iterator it;
    for(it=chunksOnScreen.begin(); it!=chunksOnScreen.end(); ++it){
        Vector3 chunkPos = it.value()->getPosition();
        int removePos = chunkPos.x*CHUNK_DIM*CHUNK_DIM + chunkPos.z*CHUNK_DIM + chunkPos.y;

        bool matched = false;
        //check if chunk pos matches any of the positons on screen
        foreach(int position, positionsOnScreen){
            if(position == removePos)
                matched = true;
        }
        if(!matched)
            toRemove.append(removePos);
    }

    // finally remove from screen
    foreach(int index, toRemove)
        chunksOnScreen.remove(index);
}

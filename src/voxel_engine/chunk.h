#ifndef CHUNK_H
#define CHUNK_H

#include <QList>
#include "common_engine/graphics.h"
#include "voxelmanager.h"
#include "common_engine/noisegenerator.h"
#include <map>

class VoxelManager;

class Chunk
{
public:
    Chunk();
    Chunk(int dim, VoxelManager* vm, Vector3 p);
    ~Chunk();

    struct Block{
        char c;
        bool frontVisible,
             backVisible,
             leftVisible,
             rightVisible,
             topVisible,
             bottomVisible;
    }__attribute((packed));


    virtual void render(Graphics* g);
    void renderTransparent(Graphics* g);
    void renderWater(Graphics* g);

    void addVoxel(int index, char vox);       //add voxel to list at index
    void addBlock(int index, char vox);
    Voxel* getVoxel(int index);
    Voxel* getVoxel(Vector3 i);
    Vector3 getPosition();
    void setBlockVisibility(bool front, bool back, bool left, bool right, bool top, bool bottom, int index);
    Vector3* getExtremities();

    virtual void resetVBO();     //rebuilds vbo given the logical state of the blocks
    Block* blocks;

protected:
    Vector3 pos;
    int dimension;

    char* voxels;
    VoxelManager* voxelManager;     //use this to look up char to voxel types

    int counter;                    //for vbo data
    float* vboData;
    unsigned int vboID;

    int counterTrans;                   //for transparent vbo
    float* vboDataTrans;
    unsigned int vboIDTrans;

    int counterWater;                   //water vbo
    float* vboDataWater;
    unsigned int vboIDWater;

    Vector3* extremities;           //keep track of 8 extremities of chunk

};

#endif // CHUNK_H

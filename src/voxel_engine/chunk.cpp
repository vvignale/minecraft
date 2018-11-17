#include "chunk.h"
#include <iostream>

using namespace std;

Chunk::Chunk(){}

Chunk::Chunk(int dim, VoxelManager* vm, Vector3 p)
{
    //initialize list with capacity
    dimension = dim;    //can hold up to dim*dim*dim voxels
    voxelManager = vm;
    pos = p;

    counter = 0;
    counterTrans = 0;
    counterWater = 0;
    blocks = new Block[dimension*dimension*dimension];

    //dxdxd blocks, 6 faces, 4 vertices, 5 floats
    vboData = new float[dimension*dimension*dimension*6*4*5];       //no normals in chunk
    vboDataTrans = new float[dimension*dimension*dimension*6*4*5];
    vboDataWater = new float[dimension*dimension*dimension*6*4*5];

    extremities = new Vector3[8];
    extremities[0] = pos;
    extremities[1] = Vector3(pos.x+dim,pos.y,pos.z);
    extremities[2] = Vector3(pos.x,pos.y,pos.z+dim);
    extremities[3] = Vector3(pos.x+dim,pos.y,pos.z+dim);
    extremities[4] = Vector3(pos.x,pos.y+dim,pos.z);
    extremities[5] = Vector3(pos.x+dim,pos.y+dim,pos.z);
    extremities[6] = Vector3(pos.x,pos.y+dim,pos.z+dim);
    extremities[7] = Vector3(pos.x+dim,pos.y+dim,pos.z+dim);

}

Chunk::~Chunk(){
    delete [] vboData;
    delete [] blocks;
    delete [] extremities;
}

void Chunk::addVoxel(int index, char vox){
    voxels[index] = vox;
}

Vector3* Chunk::getExtremities(){
    return extremities;
}

void Chunk::addBlock(int index, char vox){
    //make a block struct and set its char
    Block newBlock;
    newBlock.c = vox;
    blocks[index] = newBlock;
}

Vector3 Chunk::getPosition(){
    return pos;
}

Voxel* Chunk::getVoxel(int index){
    //return voxelManager->getVoxelFromType(voxels[index]);
    return voxelManager->getVoxelFromType(blocks[index].c);
}

Voxel* Chunk::getVoxel(Vector3 i){
    int index = i.x*dimension*dimension + i.z*dimension + i.y;
    return voxelManager->getVoxelFromType(blocks[index].c);
}

void Chunk::resetVBO(){}

void Chunk::setBlockVisibility(bool front, bool back, bool left, bool right, bool top, bool bottom, int index){
    Block* b = &blocks[index];
    b->frontVisible = front;
    b->backVisible = back;
    b->leftVisible = left;
    b->rightVisible = right;
    b->topVisible = top;
    b->bottomVisible = bottom;
}

void Chunk::renderWater(Graphics* g){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    GLuint id = g->textures.at("terrain");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);

    // draw all water blocks
    glBindBuffer(GL_ARRAY_BUFFER, vboIDWater);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    unsigned int stride = sizeof(float)*5;
    glVertexPointer(3,GL_FLOAT, stride, (void*)0);
    glTexCoordPointer(2, GL_FLOAT, stride, (void*)(sizeof(float)*3)); //offset in bytes
    glDrawArrays(GL_QUADS, 0, counterWater);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);

}

void Chunk::renderTransparent(Graphics *g){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    GLuint id = g->textures.at("terrain");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);

    // draw all transparent or semi transparent blocks
    glBindBuffer(GL_ARRAY_BUFFER, vboIDTrans);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    unsigned int stride = sizeof(float)*5;
    glVertexPointer(3,GL_FLOAT, stride, (void*)0);
    glTexCoordPointer(2, GL_FLOAT, stride, (void*)(sizeof(float)*3)); //offset in bytes
    glDrawArrays(GL_QUADS, 0, counterTrans);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Chunk::render(Graphics *g){

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    GLuint id = g->textures.at("terrain");
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);

    // draw all opaque blocks
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    unsigned int stride = sizeof(float)*5;          //watch stride when testing
    glVertexPointer(3,GL_FLOAT, stride, (void*)0);
    glTexCoordPointer(2, GL_FLOAT, stride, (void*)(sizeof(float)*3)); //offset in bytes
    glDrawArrays(GL_QUADS, 0, counter);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);

}

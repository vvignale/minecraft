#include "minecraftchunk.h"
#include <iostream>

#define WATER_LEVEL -2

using namespace std;

MinecraftChunk::MinecraftChunk(int dim, MinecraftWorld* w, MinecraftVoxelManager* mvm, Vector3 p,PerlinNoise* ng)
    : Chunk(dim,mvm,p)
{
    world = w;

    //set up world noise and blocks

    //Compute and store vbo data. Includes generating the positions of the blocks in chunk and determining face visibility

    //generate noise and determine terrain composition
    for(int x=0; x<dimension; x++){
        for(int z=0; z<dimension; z++){
            int depth = ng->GetHeight(x+pos.x,z+pos.z)*25;

            if(x+pos.x > 0 && x+pos.x<5 && z+pos.z>0 && z+pos.z<5)
                cout<<"Height at "<<x+pos.x<<" "<<z+pos.z<<": "<<depth<<endl;

            if(depth<-25)
                depth = -25;

            for(int y=0; y<dimension; y++){
                int index = x*dimension*dimension + z*dimension + y;

                //use absolute coordinates
                if(y+pos.y<depth && y+pos.y<WATER_LEVEL){
                    addBlock(index,'v');        //water
                }

                //water threshold
                else if(y+pos.y<depth && y+pos.y>=WATER_LEVEL+1){
                    addBlock(index,'g');

                }

                else if( (y+pos.y < depth) && y+pos.y==WATER_LEVEL){            // sandy beach
                    addBlock(index,'r');
                }

                else{
                    addBlock(index,'n');        //air
                }

                //place a general cover over the water
                if(y+pos.y<10)
                    addBlock(x*dimension*dimension + z*dimension + dimension+WATER_LEVEL-1,'w');

            }

        }
    }


    //add trees:

    for(int x=0; x<dimension; x++){
        for(int z=0; z<dimension; z++){

            int depth = ng->GetHeight(x+pos.x,z+pos.z)*25;

            // with low probability place a tree
            int num = rand() % 200;
            int treeWidth = 8;

            //if small random probability and above sand levels and within edges of chunk
            if(num < 1 && depth>WATER_LEVEL+1 && pos.y<1 &&
                    x>treeWidth/2 && x<dimension-(treeWidth/2) && z>treeWidth/2 && z<dimension-(treeWidth/2)){


                //roll another number to determine tree type
                int treeType = rand()%2;


                // acacia
                if(treeType==1){

                    QList<int> barkIndices;

                    barkIndices.append(x*dimension*dimension + z*dimension + (depth));
                    barkIndices.append(x*dimension*dimension + z*dimension + (depth+1));
                    barkIndices.append(x*dimension*dimension + z*dimension + (depth+2));

                    // lateral branches:
                    barkIndices.append((x+1)*dimension*dimension + (z)*dimension + (depth+2));
                    barkIndices.append((x+2)*dimension*dimension + (z)*dimension + (depth+3));

                    barkIndices.append((x-1)*dimension*dimension + (z)*dimension + (depth+2));
                    barkIndices.append((x-2)*dimension*dimension + (z)*dimension + (depth+3));

                    barkIndices.append((x)*dimension*dimension + (z+1)*dimension + (depth+2));
                    barkIndices.append((x)*dimension*dimension + (z+2)*dimension + (depth+3));

                    barkIndices.append((x)*dimension*dimension + (z-1)*dimension + (depth+2));
                    barkIndices.append((x)*dimension*dimension + (z-2)*dimension + (depth+3));


                    foreach(int index, barkIndices)
                        addBlock(index, 'b');


                    //save leaf indices
                    QList<int> leafIndices;
                    QList<int> opaqueleafIndices;
                    int start,end;
                    start = -3;
                    end = 4;

                    for(int i=0; i<3; i++){
                        for(int newX=start; newX<end; newX++){
                            for(int newZ=start; newZ<end; newZ++){
                                leafIndices.append((x+newX)*dimension*dimension + (z+newZ)*dimension + (depth+4));
                            }
                        }
                        depth+=1;
                        start += 1;
                        end -= 1;
                    }

                    leafIndices.append((x+3)*dimension*dimension + (z+3)*dimension + (depth));
                    leafIndices.append((x+2)*dimension*dimension + (z+2)*dimension + (depth));
                    leafIndices.append((x+1)*dimension*dimension + (z+1)*dimension + (depth));

                    leafIndices.append((x-3)*dimension*dimension + (z-3)*dimension + (depth));
                    leafIndices.append((x-2)*dimension*dimension + (z-2)*dimension + (depth));
                    leafIndices.append((x-1)*dimension*dimension + (z-1)*dimension + (depth));

                    leafIndices.append((x-3)*dimension*dimension + (z+3)*dimension + (depth));
                    leafIndices.append((x-2)*dimension*dimension + (z+2)*dimension + (depth));
                    leafIndices.append((x-1)*dimension*dimension + (z+1)*dimension + (depth));

                    leafIndices.append((x+3)*dimension*dimension + (z-3)*dimension + (depth));
                    leafIndices.append((x+2)*dimension*dimension + (z-2)*dimension + (depth));
                    leafIndices.append((x+1)*dimension*dimension + (z-1)*dimension + (depth));

                    //end leaf indices
                    foreach(int index, leafIndices)
                        addBlock(index, 'l');

                    foreach(int index, opaqueleafIndices)
                        addBlock(index, 'o');
            }


            //palm tree:
            else{

                int index = x*dimension*dimension + z*dimension + (depth); // tree
                int index1 = x*dimension*dimension + z*dimension + (depth+1);
                int index2 = x*dimension*dimension + z*dimension + (depth+2);

                addBlock(index,'p');
                addBlock(index1,'p');
                addBlock(index2,'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+3),'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+4),'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+5),'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+6),'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+7),'p');
                addBlock(x*dimension*dimension + z*dimension + (depth+8),'p');

                //save leaf indices
                QList<int> leafIndices;
                QList<int> opaqueleafIndices;

                // palm leaves
                int palmHeight = depth+9;
                leafIndices.append(x*dimension*dimension + z*dimension + (palmHeight));

                //base 4
                opaqueleafIndices.append((x+1)*dimension*dimension + z*dimension + (palmHeight));
                opaqueleafIndices.append((x-1)*dimension*dimension + z*dimension + (palmHeight));
                opaqueleafIndices.append(x*dimension*dimension + (z+1)*dimension + (palmHeight));
                opaqueleafIndices.append(x*dimension*dimension + (z-1)*dimension + (palmHeight));

                //base4 up 1
                opaqueleafIndices.append((x+1)*dimension*dimension + z*dimension + (palmHeight+1));
                opaqueleafIndices.append((x-1)*dimension*dimension + z*dimension + (palmHeight+1));
                opaqueleafIndices.append(x*dimension*dimension + (z+1)*dimension + (palmHeight+1));
                opaqueleafIndices.append(x*dimension*dimension + (z-1)*dimension + (palmHeight+1));

                //base4 up 2
                opaqueleafIndices.append((x+1)*dimension*dimension + z*dimension + (palmHeight+2));
                opaqueleafIndices.append((x-1)*dimension*dimension + z*dimension + (palmHeight+2));
                opaqueleafIndices.append(x*dimension*dimension + (z+1)*dimension + (palmHeight+2));
                opaqueleafIndices.append(x*dimension*dimension + (z-1)*dimension + (palmHeight+2));

                //base4 up 2 out 1
                leafIndices.append((x+2)*dimension*dimension + z*dimension + (palmHeight+2));
                leafIndices.append((x-2)*dimension*dimension + z*dimension + (palmHeight+2));
                leafIndices.append(x*dimension*dimension + (z+2)*dimension + (palmHeight+2));
                leafIndices.append(x*dimension*dimension + (z-2)*dimension + (palmHeight+2));

                //extended out 1
                opaqueleafIndices.append((x+2)*dimension*dimension + z*dimension + (palmHeight));
                opaqueleafIndices.append((x-2)*dimension*dimension + z*dimension + (palmHeight));
                opaqueleafIndices.append(x*dimension*dimension + (z+2)*dimension + (palmHeight));
                opaqueleafIndices.append(x*dimension*dimension + (z-2)*dimension + (palmHeight));

                //extended out 2
                leafIndices.append((x+3)*dimension*dimension + z*dimension + (palmHeight));
                leafIndices.append((x-3)*dimension*dimension + z*dimension + (palmHeight));
                leafIndices.append(x*dimension*dimension + (z+3)*dimension + (palmHeight));
                leafIndices.append(x*dimension*dimension + (z-3)*dimension + (palmHeight));

                //extended out 2 down 1
                leafIndices.append((x+3)*dimension*dimension + z*dimension + (palmHeight-1));
                leafIndices.append((x-3)*dimension*dimension + z*dimension + (palmHeight-1));
                leafIndices.append(x*dimension*dimension + (z+3)*dimension + (palmHeight-1));
                leafIndices.append(x*dimension*dimension + (z-3)*dimension + (palmHeight-1));

                //end leaf indices

                foreach(int index, leafIndices)
                    addBlock(index, 'l');
                foreach(int index, opaqueleafIndices)
                    addBlock(index, 'o');

            }

            }//end tree making

            // adding flowers
            else if(depth>=WATER_LEVEL+2 && depth<WATER_LEVEL+7 && pos.y<1){

                int num = rand() % 200;

                if(num<10){
                    int index = x*dimension*dimension + z*dimension + (depth);
                    addBlock(index,'f');
                }
            }
        }
    }

}

void MinecraftChunk::resetVBO(){

    //load texture coordinates for each block type
    Vector2 toFill1[12];
    Vector2 toFill2[12];
    Vector2 toFill3[12];
    Vector2 toFill4[12];
    Vector2 toFill5[12];
    Vector2 toFill6[12];
    Vector2 toFill7[12];
    Vector2 toFill8[12];
    Vector2 toFill9[12];
    Vector2 toFill10[12];

    //ice tcoords
    Vector2* grassCoords = voxelManager->getVoxelFromType('g')->getNormalizedTexCoords(16,toFill1);
    Vector2* glassCoords = voxelManager->getVoxelFromType('v')->getNormalizedTexCoords(16,toFill2);
    Vector2* reedCoords = voxelManager->getVoxelFromType('r')->getNormalizedTexCoords(16,toFill3);
    Vector2* barkCoords = voxelManager->getVoxelFromType('b')->getNormalizedTexCoords(16,toFill4);
    Vector2* leafCoords = voxelManager->getVoxelFromType('l')->getNormalizedTexCoords(16,toFill5);
    Vector2* waterCoords = voxelManager->getVoxelFromType('w')->getNormalizedTexCoords(16,toFill6);
    Vector2* flowerCoords = voxelManager->getVoxelFromType('f')->getNormalizedTexCoords(16,toFill7);
    Vector2* tallgrassCoords = voxelManager->getVoxelFromType('t')->getNormalizedTexCoords(16,toFill8);
    Vector2* lightbarkCoords = voxelManager->getVoxelFromType('p')->getNormalizedTexCoords(16,toFill9);
    Vector2* opaqueLeafCoords = voxelManager->getVoxelFromType('o')->getNormalizedTexCoords(16,toFill10);
    Vector2* currCoords;

    //Build vbo given logical state of blocks

    //using terrain composition, determine face visibility for each block. for visible faces, insert into vbo
    //absolute drawing position is canonical position plus chunk position plus relative block position

    //build and store a different vbo for transparent items

    counter = 0;
    counterTrans = 0;
    counterWater = 0;

    float* data;
    int* dataCounter;

    for(int x=0; x<dimension; x++){
        for(int z=0; z<dimension; z++){
            for(int y=0; y<dimension;y++){

                int indexToSet = x*dimension*dimension + z*dimension + y;       //this is the block index that will be inserted into vbo
                int indexToCheck;
                Voxel* toSet = getVoxel(indexToSet);

                if(!toSet->isTransparent() || toSet->voxelType=='w' || toSet->voxelType=='f' || toSet->voxelType=='t'){

                    //set the currcoords to be coordinates of the ice/water/whatever based on block type
                    if(blocks[indexToSet].c == 'g'){
                        currCoords = grassCoords;
                    }
                    else if(blocks[indexToSet].c == 'v'){
                        currCoords = glassCoords;
                    }
                    else if(blocks[indexToSet].c=='r')
                        currCoords = reedCoords;
                    else if(blocks[indexToSet].c=='b')
                        currCoords = barkCoords;
                    else if(blocks[indexToSet].c=='p')
                        currCoords = lightbarkCoords;
                    else if(blocks[indexToSet].c=='l')
                        currCoords = leafCoords;
                    else if(blocks[indexToSet].c=='o')
                        currCoords = opaqueLeafCoords;
                    else if(blocks[indexToSet].c=='w')
                        currCoords = waterCoords;
                    else if(blocks[indexToSet].c=='f')
                        currCoords = flowerCoords;
                    else if(blocks[indexToSet].c=='t')
                        currCoords = tallgrassCoords;

                    //check the visibility of each of 6 surrounding voxels
                    bool front = false;
                    bool back = false;
                    bool top = false;
                    bool bottom = false;
                    bool left = false;
                    bool right = false;

                    //bottom face y-1
                    indexToCheck = x*dimension*dimension + z*dimension + (y-1);

                    //switch which one setting depending on transparent or not
                    if(blocks[indexToSet].c=='l' || blocks[indexToSet].c=='f' || blocks[indexToSet].c=='t'){
                        data = vboDataTrans;
                        dataCounter = &counterTrans;
                    }
                    else if(blocks[indexToSet].c=='w'){
                        data = vboDataWater;
                        dataCounter = &counterWater;
                    }
                    else{
                        data = vboData;
                        dataCounter = &counter;
                    }


                    // classic and criss-crossed way of viewing voxel

                    // crossed voxel double sided
                    if(blocks[indexToSet].c=='f' || blocks[indexToSet].c=='t'){

                        //left face z+1
                        indexToCheck = x*dimension*dimension + (z+1)*dimension + y;
                        if((!(z+1 < dimension && !getVoxel(indexToCheck)->isTransparent()))&& blocks[indexToSet].c!='w'){
                            left = true;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }

                        //right face z-1
                        indexToCheck = x*dimension*dimension + (z-1)*dimension + y;
                        if(!(z-1 >= 0 && !getVoxel(indexToCheck)->isTransparent())&& blocks[indexToSet].c!='w'){
                            right = true;
                            data[(*dataCounter)++] = .25+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = -.25+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = -.25+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;

                            data[(*dataCounter)++] = .25+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;
                        }

                        //front x+1
                        indexToCheck = (x+1)*dimension*dimension + z*dimension + y;
                        if(!(x+1 < dimension && !getVoxel(indexToCheck)->isTransparent())&& blocks[indexToSet].c!='w'){
                            front = true;
                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }

                        //back x-1
                        indexToCheck = (x-1)*dimension*dimension + z*dimension + y;
                        if(!(x-1 >= 0 && !getVoxel(indexToCheck)->isTransparent()) && blocks[indexToSet].c!='w'){
                            back = true;
                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = 1.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = 1.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }
                    }
                    //end criss crossed voxel

                    //classic voxel
                    else{

                        if((!(y-1 >= 0 && !getVoxel(indexToCheck)->isTransparent())) && blocks[indexToSet].c!='w'){
                            bottom = true;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[4].x;
                            data[(*dataCounter)++] = currCoords[4].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[5].x;
                            data[(*dataCounter)++] = currCoords[5].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[6].x;
                            data[(*dataCounter)++] = currCoords[6].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[7].x;
                            data[(*dataCounter)++] = currCoords[7].y;
                        }

                        //top face y+1
                        indexToCheck = x*dimension*dimension + z*dimension + (y+1);
                        if(!(y+1 < dimension && !getVoxel(indexToCheck)->isTransparent())){
                            top = true;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[1].x;
                            data[(*dataCounter)++] = currCoords[1].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[0].x;
                            data[(*dataCounter)++] = currCoords[0].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[3].x;
                            data[(*dataCounter)++] = currCoords[3].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[2].x;
                            data[(*dataCounter)++] = currCoords[2].y;

                        }

                        //left face z+1
                        indexToCheck = x*dimension*dimension + (z+1)*dimension + y;
                        if((!(z+1 < dimension && !getVoxel(indexToCheck)->isTransparent()))&& blocks[indexToSet].c!='w'){
                            left = true;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }

                        //right face z-1
                        indexToCheck = x*dimension*dimension + (z-1)*dimension + y;
                        if(!(z-1 >= 0 && !getVoxel(indexToCheck)->isTransparent())&& blocks[indexToSet].c!='w'){
                            right = true;
                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;
                        }

                        //front x+1
                        indexToCheck = (x+1)*dimension*dimension + z*dimension + y;
                        if(!(x+1 < dimension && !getVoxel(indexToCheck)->isTransparent())&& blocks[indexToSet].c!='w'){
                            front = true;
                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = .5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }

                        //back x-1
                        indexToCheck = (x-1)*dimension*dimension + z*dimension + y;
                        if(!(x-1 >= 0 && !getVoxel(indexToCheck)->isTransparent()) && blocks[indexToSet].c!='w'){
                            back = true;
                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[8].x;
                            data[(*dataCounter)++] = currCoords[8].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 0+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[9].x;
                            data[(*dataCounter)++] = currCoords[9].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = .5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[10].x;
                            data[(*dataCounter)++] = currCoords[10].y;

                            data[(*dataCounter)++] = -.5+pos.x+x;
                            data[(*dataCounter)++] = 1+pos.y+y;
                            data[(*dataCounter)++] = -.5+pos.z+z;

                            data[(*dataCounter)++] = currCoords[11].x;
                            data[(*dataCounter)++] = currCoords[11].y;
                        }

                    }

                    setBlockVisibility(front,back,left,right,top,bottom,indexToSet);
                }
            }
        }
    }

    //DONE WITH SECOND LOOP

    //initialize opaque buffer

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float))*counter, vboData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //initialize transparent buffer
    glGenBuffers(1, &vboIDTrans);
    glBindBuffer(GL_ARRAY_BUFFER, vboIDTrans);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float))*counterTrans, vboDataTrans, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //initialize water buffer
    glGenBuffers(1, &vboIDWater);
    glBindBuffer(GL_ARRAY_BUFFER, vboIDWater);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(float))*counterWater, vboDataWater, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}


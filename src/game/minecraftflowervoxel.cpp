#include "minecraftflowervoxel.h"

MinecraftFlowerVoxel::MinecraftFlowerVoxel(bool t, bool p,int div,string tex,char type)
    : Voxel(t,p,div,tex,type)
{
    int random = rand()%2;


//    if(random==1){
        topIndex = Vector2(0,14);
        bottomIndex = Vector2(0,14);
        sideIndex = Vector2(0,13);
//    }
//    else{
//        topIndex = Vector2(0,14);
//        bottomIndex = Vector2(0,14);
//        sideIndex = Vector2(1,14);
//    }


}

MinecraftFlowerVoxel::~MinecraftFlowerVoxel()
{

}


#include "voxel.h"

Voxel::Voxel(bool t, bool p, int div,string tex,char type)
{
    voxelType = type;
    transparent = t;
    texture = tex;
    passable = p;
    numDiv = div;

    topIndex = Vector2(0,0);
    bottomIndex = Vector2(0,0);
    sideIndex = Vector2(0,0);

}

char Voxel::getType(){
    return voxelType;
}

//return normalized coordinates for each 4 of top,bottom,left,right indices
Vector2* Voxel::getNormalizedTexCoords(int numDivisions, Vector2 toFill[]){

    float increment = 1.0/numDivisions;
    int counter=0;
    Vector2 bottomLeft,topRight;

    //top index:
    bottomLeft = Vector2(topIndex.y*increment, 1.-((topIndex.x+1)*increment));
    topRight = Vector2((topIndex.y+1)*increment, 1.-(topIndex.x*increment));
    toFill[counter++] = bottomLeft;
    toFill[counter++] = Vector2(topRight.x,bottomLeft.y);
    toFill[counter++] = topRight;
    toFill[counter++] = Vector2(bottomLeft.x,topRight.y);

    //bottom index:
    bottomLeft = Vector2(bottomIndex.y*increment, 1.-((bottomIndex.x+1)*increment));
    topRight = Vector2((bottomIndex.y+1)*increment, 1.-(bottomIndex.x*increment));
    toFill[counter++] = bottomLeft;
    toFill[counter++] = Vector2(topRight.x,bottomLeft.y);
    toFill[counter++] = topRight;
    toFill[counter++] = Vector2(bottomLeft.x,topRight.y);

    //side index:
    bottomLeft = Vector2(sideIndex.y*increment, 1.-((sideIndex.x+1)*increment));
    topRight = Vector2((sideIndex.y+1)*increment, 1.-(sideIndex.x*increment));
    toFill[counter++] = bottomLeft;
    toFill[counter++] = Vector2(topRight.x,bottomLeft.y);
    toFill[counter++] = topRight;
    toFill[counter++] = Vector2(bottomLeft.x,topRight.y);

    return toFill;
}

void Voxel::render(Graphics* g){}

bool Voxel::isTransparent(){
    return transparent;
}

#ifndef VOXEL_H
#define VOXEL_H

#include <iostream>
#include "common_engine/vector.h"
#include "common_engine/graphics.h"
#include <list>


class Voxel
{
public:
    Voxel(bool t, bool p, int div,string tex,char type);
    virtual void render(Graphics* g);

    Vector2* getNormalizedTexCoords(int numDivisions, Vector2 toFill[]);
    bool isTransparent();
    Vector2 topIndex, bottomIndex, sideIndex;
    virtual char getType();
    int numDiv;
    char voxelType;
    bool transparent, passable;
    string texture;

    enum face{
        bottom,top,right,left,front,back,none
    };

protected:


};

#endif // VOXEL_H

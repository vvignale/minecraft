#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : Shape
{
public:
    Rectangle(Vector3 pos, Vector3 c, Vector3 dim);

private:
    float x,y,z;
};

#endif // RECTANGLE_H

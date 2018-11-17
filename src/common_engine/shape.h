#ifndef SHAPE_H
#define SHAPE_H

#include "vector.h"
#include "graphics.h"
#include "range.h"

class Cylinder;

class Shape
{
public:
    Shape(Vector3 pos, Vector3 c);

    //collisions returning mtv
    virtual Vector3 collide(Shape* s);
    virtual Vector3 collideCylinder(Cylinder* c);
    void updatePosition(Vector3 delta);
    virtual void render(Graphics* g);
    virtual Range getRange();
    Vector3 getColor();
    Vector3 getPosition();
    Vector3 position;

protected:
    Vector3 color;
    Range range;
    float intervalMTV(Range a, Range b);


};

#endif // SHAPE_H

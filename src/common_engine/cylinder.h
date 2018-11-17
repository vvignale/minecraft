#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape.h"

class Cylinder : public Shape
{
public:
    Cylinder(Vector3 center, float r, float h, Vector3 c);
    void render(Graphics* g);
    Vector3 collide(Shape *s);
    Vector3 collideCylinder(Cylinder *c);

    float getRadius();
    float getHeight();
    Range getRange();

private:
    float radius, height;

};

#endif // CYLINDER_H

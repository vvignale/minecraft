#include "shape.h"

Shape::Shape(Vector3 pos, Vector3 c)
{
    position = pos;
    color = c;
}

void Shape::render(Graphics* g){}

void Shape::updatePosition(Vector3 delta){
    position += delta;
}

Vector3 Shape::getPosition(){
    return position;
}

Vector3 Shape::getColor(){
    return color;
}

Vector3 Shape::collide(Shape* s){}

Vector3 Shape::collideCylinder(Cylinder* c){}

Range Shape::getRange(){}

float Shape::intervalMTV(Range a, Range b){
    //at the moment assuming that max and min are with respect to y only
    float aRight = b.getMax().y-a.getMin().y;
    float aLeft = a.getMax().y - b.getMin().y;

    if(aRight<0 || aLeft<0)
        return NULL;
    if(aRight<aLeft)
        return aRight;
    else
        return -aLeft;
}



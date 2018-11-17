#include "cylinder.h"
#include <iostream>

using namespace std;

Cylinder::Cylinder(Vector3 center, float r, float h, Vector3 c)
    : Shape(center,c)
{
    radius = r;
    height = h;
    range = Range(center, Vector3(center.x,center.y+h,center.z));
}

float Cylinder::getRadius(){
    return radius;
}

float Cylinder::getHeight(){
    return height;
}

Range Cylinder::getRange(){
    return range;
}

void Cylinder::render(Graphics* g){
    g->renderCylinder(position, radius, height,color);
}

Vector3 Cylinder::collide(Shape *s){
    return s->collideCylinder(this);        //may need adjusting for pointer to self
}

Vector3 Cylinder::collideCylinder(Cylinder *c){

    Vector3 mtv1,mtv2;
    float mag1, mag2;       //store whichever magnitude is easier to translate out of

    Vector3 p2 = c->getPosition();
    float r2 = c->getRadius();

    //check if the caps overlap from a topdown view:
    float dist = (position - p2).lengthSquared();
    float maxDist = (radius+r2)*(radius+r2);

    if(dist<maxDist){
        //disks overlaps from the top, get the first mtv
        float len = (position-p2).length();
        mtv1 = (p2-position)/len * ((radius+r2)-len);
        mag1 = mtv1.length();
    }
    else        //not overlapping in the top view
        return Vector3(0,0,0);


    //check for interval overlaps from a side view:
    float sideMag = Shape::intervalMTV(this->getRange(), c->getRange());
    if(sideMag==NULL)
        return Vector3(0,0,0);    //not overlapping in the side view
    else{
        mtv2 = Vector3(0,1,0)*sideMag;
        //cout<<"Second mtv: "<<mtv2<<endl;
        mag2 = mtv2.length();
    }

    //translate out of collision by lower amount
    if(mag1<mag2 || mtv2.isZeroVector())
        return mtv1;
    return mtv2;
}

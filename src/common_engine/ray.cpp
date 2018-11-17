#include "ray.h"

Ray::Ray(Vector3 o, Vector3 d)
{
    origin = o;
    direction = d;
}

//intersect this ray with plane defined by normal and point. returns t
float Ray::intersectPlane(Vector3 planeNormal, Vector3 pointInPlane){
    return -(planeNormal.dot(origin-pointInPlane)) / (planeNormal.dot(direction));
}




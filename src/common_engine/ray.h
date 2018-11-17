#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray
{
public:
    Ray(Vector3 o, Vector3 d);
    Vector3 origin,direction;
    float intersectPlane(Vector3 planeNormal, Vector3 pointInPlane);
};

#endif // RAY_H

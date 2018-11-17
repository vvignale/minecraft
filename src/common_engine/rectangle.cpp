#include "rectangle.h"

Rectangle::Rectangle(Vector3 pos, Vector3 c, Vector3 dim)
    : Shape(pos,c)
{
    x = dim.x;
    y = dim.y;
    z = dim.z;
}

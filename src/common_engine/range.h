#ifndef RANGE_H
#define RANGE_H

#include "vector.h"

class Range
{
public:
    Range();
    Range(Vector3 start, Vector3 end);
    Vector3 getMin();
    Vector3 getMax();

private:
    Vector3 min, max;
};

#endif // RANGE_H

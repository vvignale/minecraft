#include "range.h"

Range::Range(){}

Range::Range(Vector3 start, Vector3 end)
{
    min = start;
    max = end;
}

Vector3 Range::getMin(){
    return min;
}

Vector3 Range::getMax(){
    return max;
}

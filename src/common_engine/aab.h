#ifndef AAB_H
#define AAB_H

#include "shape.h"

class AAB : public Shape
{
public:
    AAB(Vector3 pos, int s, Vector3 c, QList<Vector2> tCoords, string tex);
    void render(Graphics* g);

protected:
    int sideLength;
    QList<Vector2> texCoords;
    string texID;
};

#endif // AAB_H

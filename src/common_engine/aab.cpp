#include "aab.h"
#include <iostream>

using namespace std;

//axis aligned box shape. used for player visualization

AAB::AAB(Vector3 pos, int s, Vector3 c, QList<Vector2> tCoords,string tex)
    : Shape(pos,c)
{
    sideLength = s;
    texCoords = tCoords;
    texID = tex;
}

void AAB::render(Graphics* g){
    g->renderAAB(texID, texCoords, 16, position, color, sideLength);
}

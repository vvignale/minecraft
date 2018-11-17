#include "wall.h"

#include <iostream>

using namespace std;

Wall::Wall(Vector3 pos, Vector3 dim, Vector3 n)
    : StaticPhysicsEntity(pos,dim)
{
    normal = n;
}

void Wall::render(Graphics *g){
    //cout<<"rendering a wall"<<endl;
    //g->renderXYQuad(position, dimensions);
}

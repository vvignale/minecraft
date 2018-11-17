#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GL_GLEXT_PROTOTYPES
#include <qgl.h>
#include <glu.h>
#include <string>
#include <map>
#include "vector.h"
#include <QPair>

using namespace std;

class Graphics
{
public:
    Graphics();
    ~Graphics();

    GLuint loadTexture(string path, string name);
    void renderQuad(string idName);
    void renderCylinder(Vector3 pos, float radius, float height, Vector3 color);
    void renderAAB(string idName, QList<Vector2> tCoords,int numDiv, Vector3 pos, Vector3 color, float scale);
    void renderVoxelFace(int face, Vector3 offset);
    void renderLine(Vector3 start, Vector3 end);
    void renderSkybox(Vector3 pos);

    QPair<Vector2,Vector2> getNormalizedTexCoords(Vector2 index, int numDivisions);

    map<string, GLuint> textures;

private:

    GLUquadric* quadric;
};

#endif // GRAPHICS_H

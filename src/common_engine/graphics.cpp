#include "graphics.h"
#include <QtGui/QImage>
#include <QGLWidget>
#define EPSILON .001
#include <iostream>

using namespace std;

Graphics::Graphics()
{
    textures.clear();
    quadric = gluNewQuadric();
}

Graphics::~Graphics(){
    //delete all items in hashmap
    for (std::map<string,GLuint>::iterator it=textures.begin(); it!=textures.end(); ++it){
        glDeleteTextures(1, &(textures.at(it->first)));
//        std::cout << "Texture \""<<it->first << "\" deleted " << std::endl;
    }
    delete quadric;
}

GLuint Graphics::loadTexture(string path, string name){

    QImage img(QString::fromStdString(path));
    img = QGLWidget::convertToGLFormat(img);
    if(img.isNull())
        cout<<"Invalid path, no image loaded"<<endl;
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());

    textures.insert(pair<string, GLuint>(name, id));
//    cout<<"Texture \""<<name<<"\" loaded"<<endl;
    return id;
}

//support for drawing from a texture atlas
QPair<Vector2,Vector2> Graphics::getNormalizedTexCoords(Vector2 index, int numDivisions)
{
    float increment = 1.0/numDivisions;
    Vector2 bottomLeft = Vector2(index.y*increment, 1.-((index.x+1)*increment));
    Vector2 topRight = Vector2((index.y+1)*increment, 1.-(index.x*increment));
    return QPair<Vector2,Vector2>(bottomLeft,topRight);
}

void Graphics::renderLine(Vector3 start, Vector3 end){
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
}


void Graphics::renderVoxelFace(int face, Vector3 offset){

    glBegin(GL_QUADS);
    //depending on which face, render in different plane

    if(face==0){  //bottom
        glVertex3f(-.5+offset.x,0+offset.y-EPSILON,-.5+offset.z);
        glVertex3f(.5+offset.x,0+offset.y-EPSILON,-.5+offset.z);
        glVertex3f(.5+offset.x,0.+offset.y-EPSILON,.5+offset.z);
        glVertex3f(-.5+offset.x,0.+offset.y-EPSILON,.5+offset.z);
    }
    else if(face==1){   //top
        glVertex3f(.5+offset.x,1.+offset.y+EPSILON,-.5+offset.z);
        glVertex3f(-.5+offset.x,1.+offset.y+EPSILON,-.5+offset.z);
        glVertex3f(-.5+offset.x,1.+offset.y+EPSILON,.5+offset.z);
        glVertex3f(.5+offset.x,1.+offset.y+EPSILON,.5+offset.z);

    }
    else if(face==2){   //right
        glVertex3f(-.5+offset.x,0+offset.y,.5+offset.z+EPSILON);
        glVertex3f(.5+offset.x,0+offset.y,.5+offset.z+EPSILON);
        glVertex3f(.5+offset.x,1+offset.y,.5+offset.z+EPSILON);
        glVertex3f(-.5+offset.x,1+offset.y,.5+offset.z+EPSILON);
    }
    else if(face==3){   //left
        glVertex3f(.5+offset.x,0+offset.y,-.5+offset.z-EPSILON);
        glVertex3f(-.5+offset.x,0+offset.y,-.5+offset.z-EPSILON);
        glVertex3f(-.5+offset.x,1+offset.y,-.5+offset.z-EPSILON);
        glVertex3f(.5+offset.x,1+offset.y,-.5+offset.z-EPSILON);
    }
    else if(face==4){   //front
        glVertex3f(.5+offset.x+EPSILON,0+offset.y,.5+offset.z);
        glVertex3f(.5+offset.x+EPSILON,0+offset.y,-.5+offset.z);
        glVertex3f(.5+offset.x+EPSILON,1+offset.y,-.5+offset.z);
        glVertex3f(.5+offset.x+EPSILON,1+offset.y,.5+offset.z);
    }
    else if (face==5){  //back
        glVertex3f(-.5+offset.x-EPSILON,0+offset.y,-.5+offset.z);
        glVertex3f(-.5+offset.x-EPSILON,0+offset.y,.5+offset.z);
        glVertex3f(-.5+offset.x-EPSILON,1+offset.y,.5+offset.z);
        glVertex3f(-.5+offset.x-EPSILON,1+offset.y,-.5+offset.z);
    }
    glEnd();

//    glTranslatef(-.5,0,-.5);

}

void Graphics::renderSkybox(Vector3 pos){

    GLuint id;
    glEnable(GL_TEXTURE_2D);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
//    glDepthMask(GL_TRUE);

    int sideLength = 100;

    id = textures.at("posx");
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    //back:     (x had to be reversed)
    glTexCoord2f(0,0);
    glVertex3f(-sideLength+pos.x,-sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(1,0);
    glVertex3f(-sideLength+pos.x,-sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,1);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(0,1);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);

    glEnd();

    id = textures.at("negx");
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    //front
    glTexCoord2f(0,0);
    glVertex3f(sideLength+pos.x,-sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,0);
    glVertex3f(sideLength+pos.x,-sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(1,1);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(0,1);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);

    glEnd();


    id = textures.at("negz");
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    //left (z will be reversed)
    glTexCoord2f(0,0);
    glVertex3f(-sideLength+pos.x,-sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,0);
    glVertex3f(sideLength+pos.x,-sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,1);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(0,1);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);

    glEnd();

    id = textures.at("posz");
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    //left (z will be reversed)
    glTexCoord2f(0,0);
    glVertex3f(sideLength+pos.x,-sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(1,0);
    glVertex3f(-sideLength+pos.x,-sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(1,1);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(0,1);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);

    glEnd();

    id = textures.at("posy");
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    // top
    glTexCoord2f(0,0);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,0);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,-sideLength+pos.z);
    glTexCoord2f(1,1);
    glVertex3f(sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);
    glTexCoord2f(0,1);
    glVertex3f(-sideLength+pos.x,sideLength+pos.y,sideLength+pos.z);

    glEnd();

}

void Graphics::renderAAB(string idName, QList<Vector2> tCoords,int numDiv, Vector3 pos, Vector3 color, float scale){

    //render voxel as a 1x1x1 cube with texture map sampled at all 6 sides top, bottom and side
    QPair<Vector2,Vector2> bottom,top,right,left,front,back;

    GLuint id = textures.at(idName);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    bottom = this->getNormalizedTexCoords(tCoords.at(0), numDiv);
    top = this->getNormalizedTexCoords(tCoords.at(1), numDiv);
    right = this->getNormalizedTexCoords(tCoords.at(2), numDiv);
    left = this->getNormalizedTexCoords(tCoords.at(3), numDiv);
    front = this->getNormalizedTexCoords(tCoords.at(4), numDiv);
    back = this->getNormalizedTexCoords(tCoords.at(5), numDiv);

    glTranslatef(-.5,0,-.5);

    glBegin(GL_QUADS);
    //orderings going bottom left to top right

    //bottom:
    glTexCoord2f(bottom.first.x,bottom.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(bottom.second.x,bottom.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(bottom.second.x,bottom.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(bottom.first.x,bottom.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);

    //front side:
    glTexCoord2f(front.first.x,front.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(front.second.x,front.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(front.second.x,front.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(front.first.x,front.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);

    //back side:
    glTexCoord2f(back.first.x,back.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(back.second.x,back.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(back.second.x,back.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(back.first.x,back.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);

    //left side:
    glTexCoord2f(left.first.x,left.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(left.second.x,left.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(left.second.x,left.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(left.first.x,left.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);

    //right side:
    glTexCoord2f(right.second.x,right.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(right.first.x,right.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,-.5-((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(right.first.x,right.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(right.second.x,right.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);

    //top:
    glTexCoord2f(top.second.x,top.first.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(top.first.x,top.first.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,-.5-((scale-1)/2)+pos.z);
    glTexCoord2f(top.first.x,top.second.y);
    glVertex3f(-.5-((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);
    glTexCoord2f(top.second.x,top.second.y);
    glVertex3f(.5+((scale-1)/2)+pos.x,.5+((scale-1)/2)+pos.y,.5+((scale-1)/2)+pos.z);


    glEnd();

    glTranslatef(.5,0,.5);


}


void Graphics::renderQuad(string idName){

    GLuint id = textures.at(idName);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);

    glBegin(GL_QUADS);
    glTexCoord2f(0.,0.);
    glVertex3f(-.5,0.,-.5);
    glTexCoord2f(1.,0.);
    glVertex3f(.5,0.,-.5);
    glTexCoord2f(1.,1.);
    glVertex3f(.5,0.,.5);
    glTexCoord2f(0.,1.);
    glVertex3f(-.5,0.,.5);
    glEnd();
}

void Graphics::renderCylinder(Vector3 pos, float radius, float height, Vector3 color){

    glDisable(GL_TEXTURE_2D);
    glColor3f(color.x, color.y, color.z);
    glTranslatef(pos.x, pos.y+height, pos.z);
    glRotatef(90,1,0,0);
    gluCylinder(quadric, radius, radius, height, 20, 20);
    glRotatef(-90,1,0,0);
    glTranslatef(-pos.x, -(pos.y+height), -pos.z);
}



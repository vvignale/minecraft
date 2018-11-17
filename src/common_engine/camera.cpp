#include "camera.h"
#include <iostream>

#define ZOOM 10
#define EPSILON .2

using namespace std;

Camera::Camera(Vector3 pos)
{
    currentPersp = thirdPerson;
    eyeLevel = 1.0;

    pitchAngle = 0;
    yawAngle = 0;

    eye = Vector4(pos.x, pos.y+eyeLevel, pos.z, 1);
    center = Vector4(cos(yawAngle),sin(pitchAngle)+eyeLevel,sin(yawAngle),1.0);
    up = Vector4(0.0,1.0,.0,1.0);

    look = center-eye;
    normalizedLook = Vector3(look.x,look.y,look.z);
    normalizedLook.normalize();

    r0 = Vector4(0,0,0,0);
    r1 = Vector4(0,0,0,0);
    r2 = Vector4(0,0,0,0);
    r3 = Vector4(0,0,0,0);
}

Camera::~Camera()
{}

Vector3 Camera::getEye(){
    return Vector3(eye.x,eye.y,eye.z);
}

void Camera::updateCenter(float deltaPitch, float deltaYaw){

    pitchAngle += deltaPitch*-.1;
    yawAngle += deltaYaw*.1;

    if(pitchAngle>90)
        pitchAngle=90-EPSILON;
    if(pitchAngle<-90)
        pitchAngle=-90+EPSILON;

    center.y = sin(pitchAngle*M_PI/180)+eye.y;
    float horizontalProj = cos(pitchAngle*M_PI/180);
    center.z = (sin(yawAngle*M_PI/180)*horizontalProj)+eye.z;
    center.x = (cos(yawAngle*M_PI/180)*horizontalProj)+eye.x;

    look = center - eye;
    normalizedLook = Vector3(look.x,look.y,look.z);
    normalizedLook.normalize();
}

//Culls a chunk (AAB) against the viewing volume
bool Camera::isInView(Chunk* c){

    Vector3* extremities = c->getExtremities();

    //Iterate though clipping planes and for each check if all 8 extremities are behind. if so, return false for not in view. if complete, return true
    for(int i=0; i<6; i++){

        Vector4 currPlane = clippingPlanes[i];
        int behindCounter = 0;

        for(int j=0; j<8; j++){
            //for each extremity, check if it is behind the plane by solving equation against current plane
            Vector3 extremity = extremities[j];
            if((currPlane.x*extremity.x + currPlane.y*extremity.y + currPlane.z*extremity.z + currPlane.w) < 0){
                behindCounter += 1;
            }
        }
        //if behind counter is 8, then all 8 extremities were behind this plane. this chunk isn't in view
        if(behindCounter==8)
            return false;
    }
    return true;
}

void Camera::update(Vector3 playerPos){

    //update camera to follow player
    eye = Vector4(playerPos.x-0.5, playerPos.y+eyeLevel, playerPos.z-.5, 1);

    if(currentPersp==thirdPerson){
        eye = eye - ZOOM*Vector4(normalizedLook,0);
    }

    updateCenter(0,0);
    updatemvpRows();            //naive reconstruction

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1.2, .01, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z,up.x,up.y,up.z);

}

void Camera::updatemvpRows(){

    //projection and modelview matrices
    GLfloat p[16];
    GLfloat mv[16];

    glGetFloatv(GL_PROJECTION_MATRIX, p);
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);

    //multiply for rows
    r0 = Vector4(p[0]*mv[0]+p[4]*mv[1]+p[8]*mv[2]+p[12]*mv[3], p[0]*mv[4]+p[4]*mv[5]+p[8]*mv[6]+p[12]*mv[7], p[0]*mv[8]+p[4]*mv[9]+p[8]*mv[10]+p[12]*mv[11], p[0]*mv[12]+p[4]*mv[13]+p[8]*mv[14]+p[12]*mv[15]);

    r1 = Vector4(p[1]*mv[0]+p[5]*mv[1]+p[9]*mv[2]+p[13]*mv[3], p[1]*mv[4]+p[5]*mv[5]+p[9]*mv[6]+p[13]*mv[7], p[1]*mv[8]+p[5]*mv[9]+p[9]*mv[10]+p[13]*mv[11], p[1]*mv[12]+p[5]*mv[13]+p[9]*mv[14]+p[13]*mv[15]);

    r2 = Vector4(p[2]*mv[0]+p[6]*mv[1]+p[10]*mv[2]+p[14]*mv[3], p[2]*mv[4]+p[6]*mv[5]+p[10]*mv[6]+p[14]*mv[7], p[2]*mv[8]+p[6]*mv[9]+p[10]*mv[10]+p[14]*mv[11], p[2]*mv[12]+p[6]*mv[13]+p[10]*mv[14]+p[14]*mv[15]);

    r3 = Vector4(p[3]*mv[0]+p[7]*mv[1]+p[11]*mv[2]+p[15]*mv[3], p[3]*mv[4]+p[7]*mv[5]+p[11]*mv[6]+p[15]*mv[7], p[3]*mv[8]+p[7]*mv[9]+p[11]*mv[10]+p[15]*mv[11], p[3]*mv[12]+p[7]*mv[13]+p[11]*mv[14]+p[15]*mv[15]);

    clippingPlanes[0] = r3 - r0;
    clippingPlanes[1] = r3 - r1;
    clippingPlanes[2] = r3 - r2;
    clippingPlanes[3] = r3 + r0;
    clippingPlanes[4] = r3 + r1;
    clippingPlanes[5] = r3 + r2;

}

void Camera::toggle(){
    if(currentPersp==firstPerson)
        currentPersp = thirdPerson;
    else
        currentPersp = firstPerson;
}

Vector4 Camera::getLookVector(){
    return center-eye;
}


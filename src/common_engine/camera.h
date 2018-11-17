#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "graphics.h"
#include "voxel_engine/chunk.h"

class Camera
{
public:
    Camera(Vector3 pos);
    ~Camera();
    Vector4 eye, center, up;
    float pitchAngle, yawAngle;
    void updateCenter(float deltaPitch, float deltaYaw);
    void update(Vector3 playerPos);
    Vector4 getLookVector();
    Vector3 getEye();
    void toggle();
    void updatemvpRows();
    bool isInView(Chunk* c);
    enum Perspective{
        firstPerson, thirdPerson
    };
    Vector3 normalizedLook;

private:
    Perspective currentPersp;
    Vector4 look;
    float aspectRatio;
    float eyeLevel;
    Vector4 r0,r1,r2,r3;    //current mvp rows
    Vector4 clippingPlanes [6];

};

#endif // CAMERA_H

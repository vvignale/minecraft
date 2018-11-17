#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "physicsentity.h"
#include "cylinder.h"
//#include "graphics.h"
#include "aab.h"

class Player : public PhysicsEntity
{
public:
    Player(Vector3 pos, Vector3 dim, World* w);
    ~Player();

    enum Direction {FORWARD, BACKWARD, LEFT, RIGHT};

    void move(Direction dir);
    void jump();

    void adjustLook(float deltaPitch, float deltaYaw);
    void updateVelocity();
    void toggleCamera();
    void onTick(float secSincePrev);
    void moveVertically(int mode);

    Vector3 getLookDirection();
    Vector3 getEye();
    Camera* camera;

private:
    Vector3 horizontalAccel;
    float yVelocity;

};

#endif // PLAYER_H

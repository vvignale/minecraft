#include "minecraftapp.h"

MinecraftApp::MinecraftApp() : Application()
{
    initializeGL();
}

void MinecraftApp::initializeGL(){
    glCullFace(GL_FRONT);
}

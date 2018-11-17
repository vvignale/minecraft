#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include <QFile>
#include <QGLShaderProgram>
#include "glm.h"

class ResourceLoader{

public:

    ResourceLoader();

/**
    A simple model struct
 **/
struct Model
{
    GLMmodel *model;
    GLuint idx;
};

/**
   A resource loader with code to handle loading shader programs.

  @author: Justin Ardini (jardini), truncated for this lab by Ben LeVeque (bleveque)
   **/

    // These return a new QGLShaderProgram.  THIS MUST BE DELETED BY THE CALLER.
    QGLShaderProgram * newVertShaderProgram(const QGLContext *context, QString vertShader);
    QGLShaderProgram * newFragShaderProgram(const QGLContext *context, QString fragShader);
    QGLShaderProgram * newShaderProgram(const QGLContext *context, QString vertShader, QString fragShader);


};

#endif // RESOURCELOADER_H

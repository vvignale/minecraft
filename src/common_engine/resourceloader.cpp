#include "resourceloader.h"

#include <QGLShaderProgram>
#include <QList>
#include <QString>
#include "glm.h"


ResourceLoader::ResourceLoader(){}

/**
    Creates a new shader program from a vert shader only
  **/
QGLShaderProgram * ResourceLoader::newVertShaderProgram(const QGLContext *context, QString vertShader)
{
    QGLShaderProgram *program = new QGLShaderProgram(context);
    program->addShaderFromSourceFile(QGLShader::Vertex, vertShader);
    program->link();
    return program;
}

/**
    Creates a new shader program from a frag shader only
  **/
QGLShaderProgram * ResourceLoader::newFragShaderProgram(const QGLContext *context, QString fragShader)
{
    QGLShaderProgram *program = new QGLShaderProgram(context);
    program->addShaderFromSourceFile(QGLShader::Fragment, fragShader);
    program->link();
    return program;
}

/**
    Creates a shader program from both vert and frag shaders
  **/
QGLShaderProgram * ResourceLoader::newShaderProgram(const QGLContext *context, QString vertShader, QString fragShader)
{
    QGLShaderProgram *program = new QGLShaderProgram(context);
    program->addShaderFromSourceFile(QGLShader::Vertex, vertShader);
    program->addShaderFromSourceFile(QGLShader::Fragment, fragShader);
    program->link();
    return program;
}

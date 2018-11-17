#ifndef VIEW_H
#define VIEW_H

#include <qgl.h>
#include <QTime>
#include <QTimer>
#include "common_engine/vector.h"

#include "common_engine/application.h"

#include "common_engine/resourceloader.h"


class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();
     void renderString(string text);
     void renderString(string text, Vector2 offset);
     void setFogState(Vector3 camPos);

private:
    QTime time;
    QTimer timer;
    float fps;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    Application* app;
    QGLShaderProgram* fogProgram;

private slots:
    void tick();
};

#endif // VIEW_H


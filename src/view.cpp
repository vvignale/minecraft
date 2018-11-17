#include "view.h"
#include <QApplication>
#include <QKeyEvent>

#include "game/minecraftapp.h"
#include "game/minecraftmainmenu.h"

using namespace std;

View::View(QWidget *parent) : QGLWidget(parent)
{
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor since this is a fullscreen app
    setCursor(Qt::BlankCursor);

    app = new MinecraftApp();
    app->pushScreen(new MinecraftMainMenu(this, app));

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The game loop is implemented using a timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
    delete app;
}

void View::initializeGL()
{
    // All OpenGL initialization *MUST* be done during or after this
    // method. Before this method is called, there is no active OpenGL
    // context and all OpenGL calls have no effect.

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    time.start();
    timer.start(1000 / 60);

    // Center the mouse, which is explained more in mouseMoveEvent() below.
    // This needs to be done here because the mouse may be initially outside
    // the fullscreen window and will not automatically receive mouse move
    // events. This occurs if there are two monitors and the mouse is on the
    // secondary monitor.
    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    const QGLContext *ctx = context();
    ResourceLoader* rs = new ResourceLoader();
    fogProgram = rs->newShaderProgram(ctx, ":/images/fog.vert", ":/images/fog.frag");

}

void View::setFogState(Vector3 camPos){
    fogProgram->setUniformValue("camX", camPos.x);
    fogProgram->setUniformValue("camY", camPos.y);
    fogProgram->setUniformValue("camZ", camPos.z);
}

void View::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1,1,1);
    renderText(10, 20, "FPS: " + QString::number((int) (fps)), this->font());

    // TODO: call your game rendering code here

    //bind the shader before drawing
//    fogProgram->bind();
    app->render();
//    fogProgram->release();
}

void View::renderString(string text)
{
    glColor3f(1,1,1);
    renderText(width()/2-70, height()/2, QString::fromStdString(text), this->font());
}

void View::renderString(string text, Vector2 offset)
{
    glColor3f(1,1,1);
    renderText(offset.x, offset.y, QString::fromStdString(text), this->font());
}

void View::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void View::mousePressEvent(QMouseEvent *event)
{
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    // This starter code implements mouse capture, which gives the change in
    // mouse position since the last mouse movement. The mouse needs to be
    // recentered after every movement because it might otherwise run into
    // the edge of the screen, which would stop the user from moving further
    // in that direction. Note that it is important to check that deltaX and
    // deltaY are not zero before recentering the mouse, otherwise there will
    // be an infinite loop of mouse move events.
    int deltaX = event->x() - width() / 2;
    int deltaY = event->y() - height() / 2;
    if (!deltaX && !deltaY) return;

    QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

    // TODO: Handle mouse movements here
    app->onMouseMoved(event, Vector2(width(), height()));
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
}

void View::wheelEvent(QWheelEvent *event)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();

    // TODO: Handle keyboard presses here
    app->onKeyPressed(event);
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    app->onKeyReleased(event);
}

void View::tick()
{
    // Get the number of seconds since the last tick (variable update rate)
    float seconds = time.restart() * 0.001f;
    fps = .02f / seconds + .98f * fps;

    // TODO: Implement the game update here
    app->onTick(seconds);

    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}

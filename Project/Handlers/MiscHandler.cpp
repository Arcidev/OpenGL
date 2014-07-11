#include "MiscHandler.h"

void MiscHandler::reshapeCallback(int width, int height)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60, (float)width / height, 0.1f, 1000.0f);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_MODELVIEW);
}

void MiscHandler::render()
{

    //Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    CameraHandler::relocate();

    glRotatef(SceneHandler::rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(SceneHandler::rotationY, 0.0f, 1.0f, 0.0f);

    ObjectHandler::drawObjects();

    //Moves back buffer content to the front buffer.
    glutSwapBuffers();
}

void MiscHandler::registerCallbacks()
{
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutKeyboardFunc(KeybordHandler::keyPressed);
    glutReshapeFunc(reshapeCallback);
    glutSpecialFunc(KeybordHandler::specialPressed);
}

void MiscHandler::initializeWindow()
{
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - SIZE_X) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - SIZE_Y) / 2);
    glutInitWindowSize(SIZE_X, SIZE_Y);
    glutCreateWindow("PV112 - projekt1");
}

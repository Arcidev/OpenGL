#include "MiscHandler.h"

GLfloat MiscHandler::light_position1[] = { -38.0f, 100.0f, -10.0f, 1.0f };
GLfloat MiscHandler::light_position2[] = { 38.0f, 100.0f, -10.0f, 1.0f };
GLfloat MiscHandler::lightDir[] = { 0.3f, -0.3f, -0.3f, 0.0f };

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
    GLfloat light_position3[] = { 50.0f + ObjectHandler::positionX, 167.0f, 85.0f, 1.0f };

    //Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    CameraHandler::relocate();

    glRotatef(SceneHandler::rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(SceneHandler::rotationY, 0.0f, 1.0f, 0.0f);

    //glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    //glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
    //glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
    //glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightDir);

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

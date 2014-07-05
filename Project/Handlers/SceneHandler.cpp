#include "SceneHandler.h"

// static member initialization
bool SceneHandler::animate = false;
bool SceneHandler::redLight = false;
bool SceneHandler::violetLight = false;
bool SceneHandler::wheatleyLight = false;

float SceneHandler::rotationX = 0.0f;
float SceneHandler::rotationY = 0.0f;

void SceneHandler::setLightning()
{
    GLfloat light_color1[] = { 1.0f, 0.0f, 0.0f };
    GLfloat light_color2[] = { 0.4f, 0.0f, 0.8f };
    GLfloat light_color3[] = { 1.0f, 1.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color3);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 40.0f);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 16.0f);
}

// adds objects into scene
void SceneHandler::create()
{
    //setLightning();
    //ObjectHandler obj;
}

void SceneHandler::togglePolygonMode()
{
    static int mode = 3;
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT + (mode++ % 3));
}

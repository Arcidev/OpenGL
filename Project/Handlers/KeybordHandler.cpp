#include "KeybordHandler.h"

void KeybordHandler::keyPressed(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case VK_ESCAPE:
            exit(0);
            return;
        case 'g':
            SceneHandler::animate = !SceneHandler::animate;
            return;
        case 'f':
            glutFullScreenToggle();
            return;
        case 'm':
            SceneHandler::togglePolygonMode();
            return;
        case 'r':
            CameraHandler::reset();
            SceneHandler::rotationX = 0.0f;
            SceneHandler::rotationY = 0.0f;
            return;
        case '1':
            SceneHandler::redLight = !SceneHandler::redLight;
            SceneHandler::redLight ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);
            return;
        case '2':
            SceneHandler::violetLight = !SceneHandler::violetLight;
            SceneHandler::violetLight ? glEnable(GL_LIGHT2) : glDisable(GL_LIGHT2);
            return;
        case '3':
            SceneHandler::wheatleyLight = !SceneHandler::wheatleyLight;
            SceneHandler::wheatleyLight ? glEnable(GL_LIGHT3) : glDisable(GL_LIGHT3);
            return;
        default:
            break;
    }

    CameraHandler::onKeyPressed(key);
}

void KeybordHandler::specialPressed(int key, int mouseX, int mouseY)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            SceneHandler::rotationX--;
            break;
        case GLUT_KEY_DOWN:
            SceneHandler::rotationX++;
            break;
        case GLUT_KEY_LEFT:
            SceneHandler::rotationY--;
            break;
        case GLUT_KEY_RIGHT:
            SceneHandler::rotationY++;
            break;
        default:
            break;
    }
}

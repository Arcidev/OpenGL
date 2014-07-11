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

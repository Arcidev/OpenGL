#include <iostream>
#include "CameraHandler.h"

// static member initialization
float CameraHandler::m_cameraX = 0.0f;
float CameraHandler::m_cameraY = 5.0f;
float CameraHandler::m_cameraZ = 20.0f;

// handle key pressed
void CameraHandler::onKeyPressed(unsigned char key)
{
    switch (key)
    {
        case 'a':
            m_cameraX--;
            break;
        case 'd':
            m_cameraX++;
            break;
        case 'w':
            m_cameraZ--;
            break;
        case 's':
            m_cameraZ++;
            break;
        case VK_SPACE:
            m_cameraY++;
            break;
        case 'x':
            m_cameraY--;
            break;
        default:
            return;
    }
}

// relocates Camera
void CameraHandler::relocate()
{
    gluLookAt(m_cameraX, m_cameraY, m_cameraZ,
        m_cameraX, m_cameraY, m_cameraZ - 5,
        0, 1, 0);
}

void CameraHandler::reset()
{
    m_cameraX = 0.0f;
    m_cameraY = 5.0f;
    m_cameraZ = 20.0f;
}

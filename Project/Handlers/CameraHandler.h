#pragma once
#include "..\GL\freeglut.h"

class CameraHandler
{
    private:
        static float m_cameraX;
        static float m_cameraY;
        static float m_cameraZ;

    public:
        static void onKeyPressed(unsigned char key);
        static void relocate();
        static void reset();
};


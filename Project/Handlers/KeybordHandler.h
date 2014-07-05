#pragma once
#include "SceneHandler.h"
#include "CameraHandler.h"

class KeybordHandler
{
    public:
        static void keyPressed(unsigned char key, int mouseX, int mouseY);
        static void specialPressed(int key, int mouseX, int mouseY);
};


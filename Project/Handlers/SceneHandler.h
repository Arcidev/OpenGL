#pragma once
#include "ObjectHandler.h"

class SceneHandler
{
    private:
        void setLightning();

    public:
        static bool animate;
        static bool redLight;
        static bool violetLight;
        static bool wheatleyLight;
        static float rotationX;
        static float rotationY;

        static void togglePolygonMode();

        void create();
};


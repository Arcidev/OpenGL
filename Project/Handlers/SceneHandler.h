#pragma once
#include "..\Shared\SharedDefines.h"

class SceneHandler
{
    private:
        vector<SceneObject> m_scenery;

        void setLightning();
        void load(string sceneName);

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


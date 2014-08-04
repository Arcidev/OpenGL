#pragma once
#include "..\Shared\SharedDefines.h"

class SceneHandler
{
    private:
        vector<SceneObject> m_scenery;

        void setLightning() const;
        void load(string sceneName);

    public:
        static bool animate;
        static float rotationX;
        static float rotationY;

        static void togglePolygonMode();

        void create() const;
};


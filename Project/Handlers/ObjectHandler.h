#pragma once
#include "..\GL\freeglut.h"
#include "..\GL\glext.h"
#include "MiscHandler.h"
#include "DebugLog.h"

typedef unsigned int uint;

enum LightingSource
{
    LIGHTSOURCE_NONE,
    LIGHTSOURCE_RED_LIGHTSABER,
    LIGHTSOURCE_VIOLET_LIGHTSABER,
    LIGHTSOURCE_WHEATLEY,
    LIGHTSOURCE_WHEATLEY_EYE
};

struct ObjectProperties
{
    float positionX, positionY, positionZ;
    float rotationX, rotationY, rotationZ;
    float size;
    bool animate;
    uint textureID, originalTextureID;
    LightingSource lightSource;
};

class ObjectHandler
{
    private:
        static float rotYAnimate;
        static vector<pair<int, ObjectProperties> > m_objectListId;
        static float redLightScale;
        static float violetLightScale;
        static bool goRight;

        uint loadTexture(const wchar_t * filename);
        void prepareObject(const char* fileName, bool texture, float* color, ObjectProperties properties);
        static inline void setObjectPosition(ObjectProperties& prop);

    public:
        ObjectHandler();
        static float positionX;
        static void drawObjects();

        void prepareObject(string fileName, wstring textureName = L"", float colorRed = 1.0f, float colorGreen = 1.0f, float colorBlue = 1.0f,
            float positionX = 0.0f, float positionY = 0.0f, float postitionZ = 0.0f, float size = 1.0f, float rotationX = 0.0f, float rotationY = 0.0f,
            float rotationZ = 0.0f, bool animate = false, LightingSource lightSource = LIGHTSOURCE_NONE);
};


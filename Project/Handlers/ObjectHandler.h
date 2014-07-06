#pragma once
#include "..\GL\freeglut.h"
#include "..\GL\glext.h"
#include "..\ObjLoader.h"

struct ObjectProperties
{
    ObjectProperties(SceneObject& object);
    Vector3f& position;
    Vector3f& rotation;
    float& size;
    bool& animate;
    uint textureID, originalTextureID;
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
        static inline void setObjectPosition(ObjectProperties& prop);

    public:
        ObjectHandler();
        static float positionX;
        static void drawObjects();

        void prepareObject(SceneObject object);
};


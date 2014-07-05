#pragma once
#include "..\GL\freeglut.h"
#include "..\GL\glext.h"
#include "..\ObjLoader.h"

typedef unsigned int uint;

struct ObjectProperties
{
    Vector3f position;
    Vector3f rotation;
    float size;
    bool animate;
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
        void prepareObject(const char* fileName, bool texture, float* color, ObjectProperties properties);
        static inline void setObjectPosition(ObjectProperties& prop);

    public:
        ObjectHandler();
        static float positionX;
        static void drawObjects();

        void prepareObject(string& fileName, wstring& textureName, float* color, Vector3f& position, float& size,
            Vector3f& rotation, bool& animate);
};


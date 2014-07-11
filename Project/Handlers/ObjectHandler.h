#pragma once
#include "..\GL\freeglut.h"
#include "..\GL\glext.h"
#include "..\ObjLoader.h"

struct ObjectProperties
{
    ObjectProperties(SceneObject& object);
    Vector3f position;
    Vector3f rotation;
    float size;
    bool animate;
    uint textureID, originalTextureID;
};

class ObjectHandler
{
    private:
        static vector<pair<int, ObjectProperties> > m_objectListId;

        uint loadTexture(const wchar_t * filename);
        static inline void setObjectPosition(ObjectProperties& prop);
        static void setSize(float& size) { glScalef(size, size, size); }
    public:
        ObjectHandler();
        static void drawObjects();

        void prepareObject(SceneObject object);
};


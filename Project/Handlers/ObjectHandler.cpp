#include "ObjectHandler.h"
#include "MiscHandler.h"
#include "DebugLog.h"

#define IL_USE_PRAGMA_LIBS
#include "..\IL\devil_cpp_wrapper.hpp"

// static member initialization
vector<pair<int, ObjectProperties> > ObjectHandler::m_objectListId;

ObjectProperties::ObjectProperties(SceneObject& object) : position(object.position), rotation(object.rotation), size(object.size),
                        animate(object.animated), textureID(0), originalTextureID(0) { }

ObjectHandler::ObjectHandler()
{
    // Configure ResIL
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
}

// loads texture
uint ObjectHandler::loadTexture(const wchar_t * filename)
{
    uint texId = 0;

    ilImage image;
    if (!image.Load((char*)filename))
    {
        wcerr << "Failed to load: " << filename << endl;
        return 0;
    }
    else
    {
        DebugLog::write("Texture loaded successfully: ");
        DebugLog::writeLine(filename);
    }

    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.Width(), image.Height(), GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

    glBindTexture(GL_TEXTURE_2D, 0);

    return texId;

}

// prepares object from file into display list
void ObjectHandler::prepareObject(SceneObject object)
{
    object.fileName = "Objects\\" + object.fileName;

    ObjectProperties properties(object);

    ObjLoader obj;
    DebugLog::write("Loading object: ");
    DebugLog::writeLine(object.fileName.c_str());

    if (!obj.Load(object.fileName.c_str()))
    {
        cerr << object.fileName << " not loaded\n";
        return;
    }

    DebugLog::writeLine("\tLoaded successfully");

    MTLMap mtlMap = obj.GetMtlMap();
    Mtl const* mtl;

    for (MTLMap::const_iterator itr = mtlMap.begin(); itr != mtlMap.end(); itr++)
    {
        mtl = &itr->second;
        if (mtl->triangles.size() == 0)
            continue;

        bool texture = false;
        if (mtl->ambientTexture != "")
        {
            wstring wstr = L"Objects\\" + wstring(mtl->ambientTexture.begin(), mtl->ambientTexture.end());
            if ((properties.textureID = loadTexture(wstr.c_str())))
            {
                texture = true;
                properties.originalTextureID = properties.textureID;
            }
        }
        
        m_objectListId.push_back(make_pair(glGenLists(1), properties));
        glNewList(m_objectListId.back().first, GL_COMPILE);

        glInterleavedArrays(GL_T2F_N3F_V3F, 0, &mtl->triangles[0]);
        glDrawArrays(GL_TRIANGLES, 0, mtl->triangles.size());

        glEndList();
    }
}

void ObjectHandler::setObjectPosition(ObjectProperties& prop)
{
    glTranslatef(prop.position.x, prop.position.y, prop.position.z);

    glRotatef(prop.rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(prop.rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(prop.rotation.z, 0.0f, 0.0f, 1.0f);
}

// draws objects from Display List
void ObjectHandler::drawObjects()
{
    ObjectProperties* prop;
    for (uint i = 0; i < m_objectListId.size(); i++)
    {
        glPushMatrix();

        prop = &m_objectListId[i].second;
        setObjectPosition(*prop);
        setSize(prop->size);

        if (m_objectListId[i].second.textureID > 0)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, prop->textureID);

            glCallList(m_objectListId[i].first);

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
        else
            glCallList(m_objectListId[i].first);

        glPopMatrix();
    }

}

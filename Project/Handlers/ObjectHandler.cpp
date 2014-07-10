#include "ObjectHandler.h"
#include "MiscHandler.h"
#include "DebugLog.h"
#define IL_USE_PRAGMA_LIBS
#include "..\IL\devil_cpp_wrapper.hpp"

// static member initialization
float ObjectHandler::rotYAnimate = 0.0f;
float ObjectHandler::positionX = 0.0f;
float ObjectHandler::redLightScale = 0.0f;
float ObjectHandler::violetLightScale = 0.0f;
bool ObjectHandler::goRight = true;
vector<pair<int, ObjectProperties> > ObjectHandler::m_objectListId;

ObjectProperties::ObjectProperties(SceneObject& object) : position(object.position), rotation(object.rotation), size(object.size),
                        animate(object.animate), textureID(0), originalTextureID(0) { }

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

    vector<Vector2f> textures = obj.GetTextures();
    vector<Vector3f> vertices = obj.GetVertices();
    vector<Vector3f> normals = obj.GetNormals();
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
        //glColor3fv(object.color);

        glBegin(GL_TRIANGLES);
        for (uint i = 0; i < mtl->triangles.size(); i++)
        {
            if (texture && (mtl->triangles[i].t0 != -1))
                glTexCoord2f(textures[mtl->triangles[i].t0].x,
                textures[mtl->triangles[i].t0].y);
            glNormal3f(normals[mtl->triangles[i].n0].x,
                normals[mtl->triangles[i].n0].y,
                normals[mtl->triangles[i].n0].z);
            glVertex3f(vertices[mtl->triangles[i].v0].x,
                vertices[mtl->triangles[i].v0].y,
                vertices[mtl->triangles[i].v0].z);

            if (texture && (mtl->triangles[i].t1 != -1))
                glTexCoord2f(textures[mtl->triangles[i].t1].x,
                textures[mtl->triangles[i].t1].y);
            glNormal3f(normals[mtl->triangles[i].n1].x,
                normals[mtl->triangles[i].n1].y,
                normals[mtl->triangles[i].n1].z);
            glVertex3f(vertices[mtl->triangles[i].v1].x,
                vertices[mtl->triangles[i].v1].y,
                vertices[mtl->triangles[i].v1].z);


            if (texture && (mtl->triangles[i].t2 != -1))
                glTexCoord2f(textures[mtl->triangles[i].t2].x,
                textures[mtl->triangles[i].t2].y);
            glNormal3f(normals[mtl->triangles[i].n2].x,
                normals[mtl->triangles[i].n2].y,
                normals[mtl->triangles[i].n2].z);
            glVertex3f(vertices[mtl->triangles[i].v2].x,
                vertices[mtl->triangles[i].v2].y,
                vertices[mtl->triangles[i].v2].z);
        }
        glEnd();
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

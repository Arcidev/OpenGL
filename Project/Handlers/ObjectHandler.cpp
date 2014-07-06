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
    //object.fileName = "Objects\\" + object.fileName;

    //bool isTextured = false;
    //ObjectProperties properties(object);
    //properties.textureID = 0;

    ///*if (object.textureName != L"")
    //{
    //    object.textureName = L"Textures\\" + object.textureName;
    //    if ((properties.textureID = loadTexture(object.textureName.c_str())))
    //    {
    //        glBindTexture(GL_TEXTURE_3D, properties.textureID);
    //        isTextured = true;
    //    }
    //}*/

    //properties.originalTextureID = properties.textureID;

    //ObjLoader obj;
    //DebugLog::write("Loading object: ");
    //DebugLog::writeLine(object.fileName.c_str());

    //if (!obj.Load(object.fileName.c_str()))
    //{
    //    cerr << object.fileName << " not loaded\n";
    //    return;
    //}

    //DebugLog::writeLine("  Loaded successfully");

    //vector<Triangle> triangles = obj.GetTriangles();
    //vector<Vector2f> textures = obj.GetTextures();
    //vector<Vector3f> vertices = obj.GetVertices();
    //vector<Vector3f> normals = obj.GetNormals();

    //m_objectListId.push_back(make_pair(glGenLists(1), properties));
    //glNewList(m_objectListId.back().first, GL_COMPILE);

    //glColor3fv(object.color);

    //glBegin(GL_TRIANGLES);
    //for (uint i = 0; i < triangles.size(); i++)
    //{
    //    /*if (texture && (triangles[i].t0 != -1))
    //        glTexCoord2f(textures[triangles[i].t0].x,
    //        textures[triangles[i].t0].y);
    //    glNormal3f(normals[triangles[i].n0].x,
    //        normals[triangles[i].n0].y,
    //        normals[triangles[i].n0].z);
    //    glVertex3f(vertices[triangles[i].v0].x,
    //        vertices[triangles[i].v0].y,
    //        vertices[triangles[i].v0].z);

    //    if (texture && (triangles[i].t1 != -1))
    //        glTexCoord2f(textures[triangles[i].t1].x,
    //        textures[triangles[i].t1].y);
    //    glNormal3f(normals[triangles[i].n1].x,
    //        normals[triangles[i].n1].y,
    //        normals[triangles[i].n1].z);
    //    glVertex3f(vertices[triangles[i].v1].x,
    //        vertices[triangles[i].v1].y,
    //        vertices[triangles[i].v1].z);


    //    if (texture && (triangles[i].t2 != -1))
    //        glTexCoord2f(textures[triangles[i].t2].x,
    //        textures[triangles[i].t2].y);
    //    glNormal3f(normals[triangles[i].n2].x,
    //        normals[triangles[i].n2].y,
    //        normals[triangles[i].n2].z);
    //    glVertex3f(vertices[triangles[i].v2].x,
    //        vertices[triangles[i].v2].y,
    //        vertices[triangles[i].v2].z);*/
    //}
    //glEnd();
    //glEndList();
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
    
}

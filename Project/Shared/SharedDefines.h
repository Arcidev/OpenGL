#pragma once
#include <ctime>
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef unsigned int uint;

struct Vector2f
{
    float x, y;
};

struct Vector3f
{
    float x, y, z;
};

struct Vector3u
{
    uint x, y, z;
};

struct Triangle
{
    float s, t;
    float nx, ny, nz;
    float vx, vy, vz;

    void setTexture(Vector2f& tex)
    {
        s = tex.x;
        t = tex.y;
    }

    void setNormal(Vector3f& normal)
    {
        nx = normal.x;
        ny = normal.y;
        nz = normal.z;
    }

    void setPosition(Vector3f& vertex)
    {
        vx = vertex.x;
        vy = vertex.y;
        vz = vertex.z;
    }
};

struct SceneObject
{
    string fileName;
    Vector3f position, rotation;

    float color[3];
    float size;
    bool animate;
};

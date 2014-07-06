#pragma once
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

struct Triangle
{
    unsigned int v0, t0, n0;
    unsigned int v1, t1, n1;
    unsigned int v2, t2, n2;
};

struct SceneObject
{
    string fileName;
    Vector3f position, rotation;

    float color[3];
    float size;
    bool animate;
};

struct Mtl
{
    string textureName;
    // material properties
    // color ??

    vector<Triangle> triangles;
};

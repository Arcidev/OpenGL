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
    string ambientTexture; // map_Ka
    string diffuseTexture; // map_Kd
    //string specularTexture; // map_Ks
    //string specularHighLightComponent; // map_Ns
    string alphaTexture; // map_d
    string bumpMap; // map_bump || bump
    //string displacementMap; // disp
    //string stencilDecalMap; // decal
    Vector3f ambientColor; // Ka
    Vector3f diffuseColor; // Kd
    Vector3f specularColor; // Ks
    //float transparency; // Tr

    vector<Triangle> triangles;
};

#pragma once
#include <fstream>
#include <iostream>
#include "Shared\SharedDefines.h"

class ObjLoader
{
    private:
        bool m_loadedMtl;
        map<string, MtlFile> m_mtlMap;
        vector<Vector3f> m_vertices;
        vector<Vector3f> m_normals;
        vector<Vector2f> m_textures;
        vector<MtlFile> m_triangles;

        void DecrementIndices(Triangle & triangle);
        bool LoadMtl(string fileName);
    public:
        ObjLoader();
        bool Load(const char * filename);

        vector<Vector3f>& GetVertices() { return m_vertices; }
        vector<Vector3f>& GetNormals() { return m_normals; }
        vector<Vector2f>& GetTextures() { return m_textures; }
        vector<MtlFile>& GetTriangles() { return m_triangles; }

        void PrintLog();
};

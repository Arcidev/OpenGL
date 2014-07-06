#include "ObjLoader.h"

ObjLoader::ObjLoader() : m_loadedMtl(false) 
{
    m_triangles.push_back(MtlFile());
}

bool ObjLoader::Load(const char * filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return false;
    }

    vector<Triangle>* triangles = &m_triangles.begin()->triangles;
    string prefix;
    while (!file.fail())
    {
        file >> prefix;

        if (prefix == "v")
        {
            Vector3f v;
            file >> v.x >> v.y >> v.z;
            m_vertices.push_back(v);
        }
        else if (prefix == "vt")
        {
            Vector2f vt;
            file >> vt.x >> vt.y;
            m_textures.push_back(vt);
        }
        else if (prefix == "vn")
        {
            Vector3f vn;
            file >> vn.x >> vn.y >> vn.z;
            m_normals.push_back(vn);
        }
        else if (prefix == "f")
        {
            Triangle t;
            char slash;
            file >> t.v0 >> slash >> t.t0 >> slash >> t.n0;
            file >> t.v1 >> slash >> t.t1 >> slash >> t.n1;
            file >> t.v2 >> slash >> t.t2 >> slash >> t.n2;
            DecrementIndices(t);
            triangles->push_back(t);
        }
        else if ((prefix == "mtllib") && !m_loadedMtl)
        {
            string mtllib;
            file >> mtllib;
            m_loadedMtl = LoadMtl(mtllib);
        }
        else if ((prefix == "usemtl") && m_loadedMtl)
        {
            string mtlName;
            file >> mtlName;

            if (m_mtlMap.find(mtlName) != m_mtlMap.end())
            {
                MtlFile& mtl = m_mtlMap[mtlName];
                m_triangles.push_back(mtl);
                triangles = &mtl.triangles;
            }
            else // mtl not defined
                triangles = &m_triangles.begin()->triangles;
        }
        file.ignore(1000, '\n');
    }

    file.close();
    return true;
}

void ObjLoader::DecrementIndices(Triangle & triangle)
{
    triangle.v0--; triangle.t0--; triangle.n0--;
    triangle.v1--; triangle.t1--; triangle.n1--;
    triangle.v2--; triangle.t2--; triangle.n2--;
}

bool ObjLoader::LoadMtl(string name)
{
    ifstream file(name);
    if (!file.is_open())
    {
        cout << "MTL file " << name << " not found" << endl;
        return false;
    }
}

void ObjLoader::PrintLog()
{
    cout << "Vertices: " << m_vertices.size() << endl;
    cout << "Normals: " << m_normals.size() << endl;
    cout << "Triangles: " << m_triangles.size() << endl;
}

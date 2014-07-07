#include "ObjLoader.h"

ObjLoader::ObjLoader() : m_loadedMtl(false) 
{
    m_mtlMap.insert(pair<string, Mtl>(MTL_NOT_DEFINED, Mtl()));
}

bool ObjLoader::Load(const char * filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return false;
    }

    vector<Triangle>* triangles = &m_mtlMap[MTL_NOT_DEFINED].triangles;
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
                triangles = &m_mtlMap[mtlName].triangles;
            else // mtl not defined
                triangles = &m_mtlMap[MTL_NOT_DEFINED].triangles;
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
    ifstream file("Objects\\" + name);
    if (!file.is_open())
    {
        cout << "MTL file " << name << " not found" << endl;
        return false;
    }

    string prefix;
    string mtlName;

    while (!file.fail())
    {
        file >> prefix;
        if (prefix == "newmtl")
        {            
            file >> mtlName;
            m_mtlMap.insert(pair<string, Mtl>(mtlName, Mtl()));
        }
        else if ((prefix == "map_Ka") && (mtlName != ""))
            file >> m_mtlMap[mtlName].ambientTexture;
        else if ((prefix == "map_Kd") && (mtlName != ""))
            file >> m_mtlMap[mtlName].diffuseTexture;
        else if ((prefix == "map_d") && (mtlName != ""))
            file >> m_mtlMap[mtlName].alphaTexture;
        else if ((prefix == "map_bump") && (mtlName != ""))
            file >> m_mtlMap[mtlName].bumpMap;
        else if ((prefix == "Ka") && (mtlName != ""))
            file >> m_mtlMap[mtlName].ambientColor.x >> m_mtlMap[mtlName].ambientColor.y >> m_mtlMap[mtlName].ambientColor.z;
        else if ((prefix == "Kd") && (mtlName != ""))
            file >> m_mtlMap[mtlName].diffuseColor.x >> m_mtlMap[mtlName].diffuseColor.y >> m_mtlMap[mtlName].diffuseColor.z;
        else if ((prefix == "Ks") && (mtlName != ""))
            file >> m_mtlMap[mtlName].specularColor.x >> m_mtlMap[mtlName].specularColor.y >> m_mtlMap[mtlName].specularColor.z;
        file.ignore(1000, '\n');
    }

    file.close();
    return true;
}

void ObjLoader::PrintLog()
{
    cout << "Vertices: " << m_vertices.size() << endl;
    cout << "Normals: " << m_normals.size() << endl;

    uint trianglesSize = 0;
    for (map<string, Mtl>::const_iterator itr = m_mtlMap.begin(); itr != m_mtlMap.end(); itr++)
        trianglesSize += itr->second.triangles.size();

    cout << "Triangles: " << trianglesSize << endl;
    cout << "Mtl Properties: " << m_mtlMap.size() << endl;
}

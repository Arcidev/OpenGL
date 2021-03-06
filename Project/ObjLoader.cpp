#include "ObjLoader.h"

ParserPropertyMap const ObjLoader::parserPropertyMap =
{
    { "map_Ka", AMBIENT_TEXTURE },
    { "map_Kd", DIFFUSE_TEXTURE },
    { "map_d", ALPHA_TEXTURE },
    { "map_bump", BUMP_MAP },

    { "Ka", AMBIENT_COLOR },
    { "Kd", DIFFUSE_COLOR },
    { "Ks", SPECULAR_COLOR },

    { "newmtl", NEW_MTL },
    { "usemtl", USE_MTL },
    { "mtllib", SET_MTL_LIB },

    { "v", VERTEX_POSITION },
    { "vt", TEXTURE_POSITION },
    { "vn", NORMAL_POSITION },
    { "f", TRIANGLE_VALUE }
};

ObjLoader::ObjLoader() : m_loadedMtl(false) 
{
    m_mtlMap.insert(make_pair(MTL_NOT_DEFINED, Mtl()));
}

ParserProperty ObjLoader::GetParserProperty(string const& prop) const
{
    ParserPropertyMap::const_iterator iter = parserPropertyMap.find(prop);
    return (iter == parserPropertyMap.end()) ? PROPERTY_NOT_DEFINED : iter->second;
}

bool ObjLoader::Load(char const* filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        return false;
    }

    vector<Triangle>* triangles = &m_mtlMap[MTL_NOT_DEFINED].triangles;
    vector<Vector3f> vertices;
    vector<Vector3f> normals;
    vector<Vector2f> textures;
    Vector3f vec3;
    Vector2f vec2;
    Vector3u values;
    Triangle triangle;
    char slash;
    string prefix;
    string str;

    while (!file.fail())
    {
        file >> prefix;

        switch (GetParserProperty(prefix))
        {
            case VERTEX_POSITION:
                file >> vec3.x >> vec3.y >> vec3.z;
                vertices.push_back(vec3);
                break;
            case TEXTURE_POSITION:
                file >> vec2.x >> vec2.y;
                textures.push_back(vec2);
                break;
            case NORMAL_POSITION:
                file >> vec3.x >> vec3.y >> vec3.z;
                normals.push_back(vec3);
                break;
            case TRIANGLE_VALUE:
                for (uint i = 0; i < 3; i++)
                {
                    file >> values.x >> slash >> values.y >> slash >> values.z;

                    triangle.setPosition(vertices[values.x - 1]);
                    triangle.setTexture(textures[values.y - 1]);
                    triangle.setNormal(normals[values.z - 1]);

                    triangles->push_back(triangle);
                }
                break;
            case SET_MTL_LIB:
                file >> str;
                m_loadedMtl = LoadMtl(str);
                break;
            case USE_MTL:
                if (m_loadedMtl)
                {
                    file >> str;

                    if (m_mtlMap.find(str) != m_mtlMap.end())
                        triangles = &m_mtlMap[str].triangles;
                    else // mtl not defined
                        triangles = &m_mtlMap[MTL_NOT_DEFINED].triangles;
                }
                break;
            default:
                break;
        }

        file.ignore(1000, '\n');
    }

    file.close();
    return true;
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
    Vector3f* _colorVector;

    while (!file.fail())
    {
        file >> prefix;

        switch (GetParserProperty(prefix))
        {
            case NEW_MTL:
                file >> mtlName;
                m_mtlMap.insert(pair<string, Mtl>(mtlName, Mtl()));
                break;
            case AMBIENT_TEXTURE:
                file >> m_mtlMap[mtlName].ambientTexture;
                break;
            case DIFFUSE_TEXTURE:
                file >> m_mtlMap[mtlName].diffuseTexture;
                break;
            case ALPHA_TEXTURE:
                file >> m_mtlMap[mtlName].alphaTexture;
                break;
            case BUMP_MAP:
                file >> m_mtlMap[mtlName].bumpMap;
                break;
            case AMBIENT_COLOR:
                _colorVector = &m_mtlMap[mtlName].ambientColor;
                file >> _colorVector->x >> _colorVector->y >> _colorVector->z;
                break;
            case DIFFUSE_COLOR:
                _colorVector = &m_mtlMap[mtlName].diffuseColor;
                file >> _colorVector->x >> _colorVector->y >> _colorVector->z;
                break;
            case SPECULAR_COLOR:
                _colorVector = &m_mtlMap[mtlName].specularColor;
                file >> _colorVector->x >> _colorVector->y >> _colorVector->z;
                break;
            default:
                break;
        }

        file.ignore(1000, '\n');
    }

    file.close();
    return true;
}

void ObjLoader::PrintLog() const
{
    uint trianglesSize = 0;
    for (map<string, Mtl>::const_iterator itr = m_mtlMap.begin(); itr != m_mtlMap.end(); itr++)
        trianglesSize += itr->second.triangles.size();

    cout << "Triangles: " << trianglesSize << endl;
    cout << "Mtl Properties: " << m_mtlMap.size() << endl;
}

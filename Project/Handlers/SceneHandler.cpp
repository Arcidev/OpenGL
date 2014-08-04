#include "SceneHandler.h"
#include "ObjectHandler.h"

// static member initialization
bool SceneHandler::animate = false;

float SceneHandler::rotationX = 0.0f;
float SceneHandler::rotationY = 0.0f;

void SceneHandler::setLightning() const
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

// adds objects into scene
void SceneHandler::create() const
{
    cout << "Set scene name" << endl;
    //string name;
    //cin >> name;
    //load(name);
    setLightning();
    time_t timer = time(NULL);
    ObjectHandler obj;
    SceneObject scene;
    scene.fileName = "Rayne.obj";
    scene.size = 15.0f;
    scene.rotation = { -90.0f, 0.0f, 0.0f };
    scene.position = { 0.0f, 0.0f, 0.0f };
    obj.prepareObject(scene);

    scene.fileName = "Battlelord.obj";
    scene.rotation = { 0.0f, 0.0f, 0.0f };
    scene.position = { 10.0f, 0.0f, 0.0f };
    scene.size = 1.0f;
    obj.prepareObject(scene);
    //for (vector<SceneObject>::iterator itr = m_scenery.begin(); itr != m_scenery.end(); itr++)
        //obj.prepareObject(*itr);

    cout << "Scene loaded in " << difftime(time(NULL), timer) << "sec" << endl;
}

void SceneHandler::load(string sceneName)
{

}

void SceneHandler::togglePolygonMode()
{
    static int mode = 3;
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT + (mode++ % 3));
}

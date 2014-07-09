#include "Handlers\MiscHandler.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);

    MiscHandler misc;
    misc.initializeWindow();
    misc.registerCallbacks();

    //SceneHandler scene;
    //scene.create();

    // Main loop
    glutMainLoop();

    return 0;
}

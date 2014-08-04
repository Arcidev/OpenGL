#pragma once
#include "ObjectHandler.h"
#include "KeybordHandler.h"

#define SIZE_X 720
#define SIZE_Y 480

class MiscHandler
{
    private:
        static void reshapeCallback(int width, int height);
        static void render();

    public:
        void registerCallbacks() const;
        void initializeWindow() const;
};

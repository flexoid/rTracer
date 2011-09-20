#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifdef WIN32
#undef main
#endif    //WIN32

#include "engine.h"
#include "scene.h"
#include "sceneparser.h"
#include "primitives/sphere.h"
#include "primitives/plane.h"
#include "primitives/prism.h"
#include "primitives/texturehplane.h"

#define HEIGHT 700
#define WIDTH 700

int main()
{
    SceneParser* sp = new SceneParser;
    Scene* scene = sp->LoadScene("../scenes/scene1.dat");
    delete sp;

    Screen* screen = new Screen(scene->camera, scene, HEIGHT, WIDTH);

    // Создаем объект Window
    Engine* engine = new Engine(HEIGHT, WIDTH);
    engine->Init(screen);

    // Цикл отрисовки
    while(engine->Run())
    {
        engine->Render();
    }

    return 0;
}


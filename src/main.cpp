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

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage:\n\trTracer <path_to_scene>\n");
        return 1;
    }

    SceneParser* sp = new SceneParser;
    Scene* scene = sp->LoadScene(argv[1]);
    delete sp;

    if (scene == 0)
    {
        printf("File %s doesn't exists\n", argv[1]);
        return 1;
    }

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


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifdef WIN32
#undef main
#endif    //WIN32

#include "engine.h"
#include "scene.h"
#include "primitives/sphere.h"

int main()
{
    Material mat1(0.1, 0.3, 0.5, 0.3, 0.8);
    Material mat2(0.2, 0.3, 0.2, 0.3, 0.8);
    Material mat3(0.3, 0.3, 0.4, 0.2, 0.8);

    Sphere* sph1 = new Sphere(Vector3(2.0f, 0.0f, 0.0f), 1.0f, ColorRGB(250, 0, 0), mat1);
    Sphere* sph2 = new Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, ColorRGB(0, 240, 0), mat2);
    Sphere* sph3 = new Sphere(Vector3(0.0f, 2.0f, 0.0f), 1.0f, ColorRGB(0, 0, 240), mat3);

    Light* light = new Light(Vector3(0.5, 0.5, 11.0), 4.0);
    Light* light2 = new Light(Vector3(5.0, 5.0, 5.0), 4.0);
    Camera* camera = new Camera(Vector3(5.0, 5.0, 4.0), Vector3::Null(), 1.0, 1.0);

    Scene* scene = new Scene(ColorRGB(20, 60, 75));
    scene->AddPrimitive(sph1);
    scene->AddPrimitive(sph2);
    scene->AddPrimitive(sph3);
    scene->AddLight(light);
    scene->AddCamera(camera);

    Screen* screen = new Screen(camera, scene, 700, 700);

    // Создаем объект Window
    Engine* engine = new Engine(700, 700);
    engine->Init(screen);

    // Цикл отрисовки
    while(engine->Run())
    {
        engine->Render();
    }

    return 0;
}


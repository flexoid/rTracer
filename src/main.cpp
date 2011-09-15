#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#ifdef WIN32
#undef main
#endif    //WIN32

#include "engine.h"
#include "scene.h"
#include "primitives/sphere.h"

#define HEIGHT 700
#define WIDTH 700

int main()
{
    Material mat1(0.1f, 0.3f, 0.5f, 0.3f, 0.8f);
    Material mat2(0.2f, 0.3f, 0.2f, 0.3f, 0.8f);
    Material mat3(0.3f, 0.3f, 0.4f, 0.2f, 0.8f);

    Sphere* sph1 = new Sphere(Vector3(2.0f, 0.0f, 0.0f), 1.0f, ColorRGB(250, 0, 0), mat1);
    Sphere* sph2 = new Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, ColorRGB(0, 240, 0), mat2);
    Sphere* sph3 = new Sphere(Vector3(0.0f, 2.0f, 0.0f), 1.0f, ColorRGB(0, 0, 240), mat3);

    Light* light = new Light(Vector3(0.5f, 0.5f, 11.0f), 4.0f);
    Light* light2 = new Light(Vector3(5.0f, 5.0f, 5.0f), 4.0f);
    Camera* camera = new Camera(Vector3(5.0f, 5.0f, 4.0f), Vector3::Null(), 1.0f, 1.0f);

    Scene* scene = new Scene(ColorRGB::Null());
    scene->AddPrimitive(sph1);
    scene->AddPrimitive(sph2);
    scene->AddPrimitive(sph3);
    scene->AddLight(light);
    scene->AddCamera(camera);

    Screen* screen = new Screen(camera, scene, HEIGHT, WIDTH);

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


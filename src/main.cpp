#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "engine.h"
#include "scene.h"
#include "primitives/sphere.h"

int main()
{
    Material mat1(0.5, 0.5, 0.7, 1.0);
    //Material mat2(0.1, 0.9, 0.3, 0.4);
    //Material mat3(0.9, 0.1, 0.2, 0.2);

    //Sphere* sph1 = new Sphere(Vector3(2.0, 2.0, 3.0), 3.0, ColorRGB(200, 70, 15), mat1);
    Sphere* sph2 = new Sphere(Vector3::Null(), 1.0, ColorRGB(250, 40, 15), mat1);
    //Sphere* sph3 = new Sphere(Vector3(-6.0, 2.0, 3.0), 4.0, ColorRGB(250, 90, 40), mat3);

    Light* light = new Light(Vector3(6.0, 6.0, 6.0), 11.0);
    Camera* camera = new Camera(Vector3(5.0, 5.0, 5.0), Vector3::Null(), 2.0, 2.0);

    Scene* scene = new Scene(ColorRGB(20, 60, 75));
    //scene->AddPrimitive(sph1);
    scene->AddPrimitive(sph2);
    //scene->AddPrimitive(sph3);
    scene->AddLight(light);
    scene->AddCamera(camera);

    Screen* screen = new Screen(camera, scene, 160, 120);

    // Создаем объект Window
    Engine* engine = new Engine(160, 120);
    engine->Init(screen);

    // Цикл отрисовки
    while(engine->Run())
    {
        engine->Render();
    }

    return 0;
}


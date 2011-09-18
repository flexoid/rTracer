#include "scene.h"

Scene::Scene() {};

Scene::Scene(ColorRGB bgColor): bgColor(bgColor) {};

Scene::~Scene()
{
    std::vector< Primitive* >::iterator ip;
    ip = primitives.begin();
    while (ip != primitives.end())
    {
        delete *ip;
        ip++;
    }
    std::vector< Light* >::iterator il;
    il = lights.begin();
    while (il != lights.end())
    {
        delete *il;
        il++;
    }
}

void Scene::AddPrimitive(Primitive* primitive)
{
    if (primitive)
        primitives.push_back(primitive);
}

void Scene::AddLight(Light* light)
{
    if (light)
        lights.push_back(light);
}

void Scene::AddCamera(Camera* camera)
{
    if (camera)
        this->camera = camera;
}

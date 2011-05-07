#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.h"

class RayTracer
{
public:
    RayTracer(Scene*);
private:
    Scene* scene;
};

#endif // RAYTRACER_H

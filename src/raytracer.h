#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.h"
#include "primitives/primitive.h"
#include "ray.h"
#include "light.h"

class RayTracer
{
public:
    RayTracer(Scene*);
    Primitive* Trace(Ray ray, Vector3& IntersectPoint);
    bool InShadow(Vector3 point, Light light);

private:
    Scene* scene;
    Vector3 Refract(Primitive* primitive, Vector3 vector, Vector3 point);
    Vector3 Reflect(Primitive* primitive, Vector3 vector, Vector3 point);
};

#endif // RAYTRACER_H

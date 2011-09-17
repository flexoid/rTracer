#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "scene.h"
#include "primitives/primitive.h"
#include "ray.h"
#include "light.h"
#include "colorrgb.h"

class RayTracer
{
public:
    RayTracer(Scene*);
    ColorRGB Color(Ray);

private:
    Primitive* Trace(Ray ray, Vector3& IntersectPoint);
    bool InShadow(Vector3 point, Light* light);

    Vector3 Refract(Primitive* primitive, Vector3 vector, Vector3 point);
    Vector3 Reflect(Primitive* primitive, Vector3 vector, Vector3 point);

    ColorRGB RefractColor(Ray, Vector3, Primitive*);
    ColorRGB ReflectColor(Ray, Vector3, Primitive*);
    ColorRGB DiffusePhongColor(Ray, Vector3, Primitive*);
    ColorRGB DiffuseLambertColor(Ray, Vector3, Primitive*);

    float PhongC, LambertC, ReflectC, RefractC, ReduceLightPowerC;
    Scene* scene;
};

#endif // RAYTRACER_H

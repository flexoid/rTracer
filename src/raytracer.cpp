#include <math.h>
#include "raytracer.h"

RayTracer::RayTracer(Scene* scene) : scene(scene)
{
}

Vector3 RayTracer::Refract(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float nv = vector.DotProduct(norm);
    float a,bf;
    if (nv>0) {
        nv = -nv;
        bf = 1;
        a = primitive->material.refractionCoeff;
    }
    else {
        a = 1 / primitive->material.refractionCoeff;
        bf = -1;
    }

    float D = 1 - a*a*(1 - nv*nv);
    if (D < 0)
        return Vector3(0,0,0);
    float b = bf*(nv*a + sqrt(D));
    return Vector3(vector*a + norm*b);
}

Vector3 RayTracer::Reflect(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float f = 2 * vector.DotProduct(norm);
    return Vector3(vector - norm*f);
}

Primitive* RayTracer::Trace(Ray ray, Vector3 &IntersectPoint)
{
    IntersectPoint = Vector3::Null();
    Primitive* primitive;

    std::vector< Primitive* >::iterator i;
    i = scene->primitives.begin();
    while (i != scene->primitives.end())
    {
        Primitive* prim = *i;
        Vector3 point = prim->Trace(ray);
        if (point != Vector3::Null() && (IntersectPoint == Vector3::Null() ||
            point.DistanceFrom(ray.from) < IntersectPoint.DistanceFrom(ray.from)))
        {
            IntersectPoint = point;
            primitive = prim;
        }
    }
    if (IntersectPoint != Vector3::Null())
        return primitive;
    else
        return 0;
}

bool RayTracer::InShadow(Vector3 point, Light light)
{
    Vector3 p;
    Primitive* primitive = Trace(Ray(light.pos, point), p);
    return !primitive;
}

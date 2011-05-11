#include <math.h>
#include "math_c.h"
#include "raytracer.h"

RayTracer::RayTracer(Scene* scene) : scene(scene)
{
}

ColorRGB RayTracer::Color(Ray ray)
{
    if(ray.dir==Vector3::Null()) return ColorRGB::Null();
    Vector3 point;
    Primitive* prim = Trace(ray,point);
    if(prim==0)
        return scene->bgColor;
    return DiffuseLambertColor(ray, point, prim)+DiffusePhongColor(ray, point, prim)+
	ReflectColor(ray, point, prim)+RefractColor(ray, point, prim);
}

Vector3 RayTracer::Refract(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float nv = vector.DotProduct(norm);
    float a,bf;
    if (nv>0) 
    {
        nv = -nv;
        bf = 1;
        a = primitive->material.refractionCoeff;
    }
    else 
    {
        a = 1 / primitive->material.refractionCoeff;
        bf = -1;
    }

    float D = 1 - a*a*(1 - nv*nv);
    if (D < 0)
        return Vector3::Null();
    float b = bf*(nv*a + sqrt(D));
    return Vector3(vector*a + norm*b);
}

Vector3 RayTracer::Reflect(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float f = 2.0f * vector.DotProduct(norm);
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
        i++;
    }
    if (IntersectPoint != Vector3::Null())
        return primitive;
    else
        return 0;
}

bool RayTracer::InShadow(Vector3 point, Light* light)
{
    Vector3 p;
    Primitive* primitive = Trace(Ray(light->pos, point), p);
    return !primitive;
}

ColorRGB RayTracer::DiffuseLambertColor(Ray ray, Vector3 point, Primitive* primitive)
{
    float Color;
    std::vector<Light*>::iterator i;
    i = scene->lights.begin();
    while (i != scene->lights.end())
    {
	Light* light = *i;
	if (InShadow(point, light)) continue;
	float cos = -primitive->Norm(point).DotProduct((point-light->pos).Norm());
	Color+=light->power*cos;
        i++;
    }
    return (primitive->Color())*Color*LambertC;
}

ColorRGB RayTracer::DiffusePhongColor(Ray ray, Vector3 point, Primitive* primitive)
{
    float Color;
    std::vector<Light*>::iterator i;
    i = scene->lights.begin();
    while (i != scene->lights.end())
    {
        Light* light = *i;
	if (InShadow(point, light)) continue;
	float vcos = -ray.dir.DotProduct(Reflect(primitive, (point - light->pos).Norm(), primitive->Norm(point)));
	if (vcos>0) Color+=light->power*pow(vcos,primitive->material.phong);
        i++;
    }
    return (primitive->Color())*Color*PhongC;
}

ColorRGB RayTracer::RefractColor(Ray ray, Vector3 point, Primitive* primitive)
{
    if (ray.power*primitive->refractC<EPS)
	return ColorRGB();
    return Color(Ray(point,Refract(primitive,ray.dir,point),ray.power*primitive->refractC))*RefractC*primitive->refractC;
}

ColorRGB RayTracer::ReflectColor(Ray ray, Vector3 point, Primitive* primitive)
{
    if (ray.power<EPS)
	return ColorRGB();
    return Color(Ray(point,Reflect(primitive,ray.dir,point),ray.power*primitive->reflectC))*ReflectC*primitive->reflectC;
}

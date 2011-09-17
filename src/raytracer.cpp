#include <math.h>
#include "math_c.h"
#include "raytracer.h"

RayTracer::RayTracer(Scene* scene) : scene(scene)
{
    LambertC = 0.8f;
    PhongC = 0.5f;
    RefractC = 0.3f;
    ReflectC = 0.5f;
    ReduceLightPowerC = 0.13f;
}

ColorRGB RayTracer::Color(Ray ray)
{
    if(ray.dir==Vector3::Null() || ray.power < EPS) return ColorRGB::Null();
    Vector3 point;
    Primitive* prim = Trace(ray,point);
    if(prim==0)
        return scene->bgColor;
    return (DiffuseLambertColor(ray, point, prim) + DiffusePhongColor(ray, point, prim) +
            ReflectColor(ray, point, prim) + RefractColor(ray, point, prim))*ray.power;
}

/*
Vector3 RayTracer::Refract(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float nv = vector.DotProduct(norm);
    float a,bf;
    if (nv>0.0f)
    {
        nv = -nv;
        bf = 1.0f;
        a = primitive->material.refractionCoeff;
    }
    else 
    {
        a = 1.0f / primitive->material.refractionCoeff;
        bf = -1.0f;
    }

    float D = 1.0f - a*a*(1.0f - nv*nv);
    if (D < 0.0f)
        return Vector3::Null();
    float b = bf*(nv*a + sqrt(D));
    return Vector3(vector*a + norm*b);
}
*/

Vector3 RayTracer::Refract(Primitive* primitive, Vector3 vector, Vector3 point)
{
    Vector3 norm = primitive->Norm(point);
    float sina = vector.DotProduct(norm);
    float n1, n2;
    if(sina>0.0f)
    {
        n2 = primitive->material.refractionCoeff;
        n1 = 1.0f;
    }
    else
    {
        n2 = 1.0f;
        n1 = primitive->material.refractionCoeff;
        sina=-sina;
        if (sina>n2) return Vector3::Null();
    }
    return (vector+norm*(sqrt((n2*n2/n1*n1-1)/sina/sina+1)-1)*sina)*n1/n2;
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
    Primitive* primitive = 0;

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
    float Color = 0.0f;
    std::vector<Light*>::iterator i;
    i = scene->lights.begin();
    while (i != scene->lights.end())
    {
        Light* light = *i;
        if (!InShadow(point, light))
        {
            Vector3 dir = point - light->pos;
            float cos = -primitive->Norm(point).DotProduct(dir.Norm());
            float power = light->power - dir.Length()*ReduceLightPowerC;
            if (power<0)
                power=0;
            if (cos>0)
                Color += power * primitive->material.lambert * cos;
        }
        i++;
    }
    return (primitive->Color())*Color*LambertC;
}

ColorRGB RayTracer::DiffusePhongColor(Ray ray, Vector3 point, Primitive* primitive)
{
    float Color = 0.0f;
    std::vector<Light*>::iterator i;
    i = scene->lights.begin();
    while (i != scene->lights.end())
    {
        Light* light = *i;
        if (!InShadow(point, light))
        {
            float vcos = -ray.dir.DotProduct(Reflect(primitive, (point - light->pos).Norm(), point));
            float power = light->power - (point - light->pos).Length()*ReduceLightPowerC;
            if (power<0)
                power=0;
            if (vcos>0) Color += power * vcos * primitive->material.phong;
        }
        i++;
    }
    return (primitive->Color())*Color*PhongC;
}

ColorRGB RayTracer::RefractColor(Ray ray, Vector3 point, Primitive* primitive)
{
    if (ray.power < EPS)
	return ColorRGB();
    ColorRGB color(Color(Ray(point, point + Refract(primitive, ray.dir, point), ray.power * primitive->material.transperancy)));
    if (color != scene->bgColor)
        return color * RefractC;
    else
        return ColorRGB::Null();
}

ColorRGB RayTracer::ReflectColor(Ray ray, Vector3 point, Primitive* primitive)
{
    if (ray.power < EPS)
	return ColorRGB();
    ColorRGB color(Color(Ray(point, point + Reflect(primitive, ray.dir, point), ray.power * primitive->material.reflectionCoeff)));
    if (color != scene->bgColor)
        return color * ReflectC;
    else
        return ColorRGB::Null();
}

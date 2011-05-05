#include "sphere.h"
#include "math.h"
#include "../math_c.h"

Sphere::Sphere(Vector3 center, float radius, ColorRGB color)
{
    this->center = center;
    this->radius = radius;
    this->color = color;
}

Vector3 Sphere::Norm(Vector3 point)
{
    return (point - center) / radius;
}

Vector3 Sphere::Trace(Ray ray)
{
    Vector3 ac=center-ray.from;
    float acs=0;
    acs = ac.x*ray.dir.x+ac.y*ray.dir.y+ac.z*ray.dir.z;
    if (acs < 0)
        return Vector3(0,0,0);
    float sqrLength=ac.Dot(ac);
    float D=acs*acs-sqrLength+radius*radius;
    if (D < 0)
        return Vector3(0,0,0);
    float t=acs-sqrt(D);
    if (t < EPS)
        t = acs+sqrt(D);
    if (t < EPS)
        return Vector3(0,0,0);
    return Vector3(ray.from.x+t*ray.dir.x,ray.from.y+t*ray.dir.y,ray.from.z+t*ray.dir.z);
}

ColorRGB Sphere::Color()
{
    return color;
}

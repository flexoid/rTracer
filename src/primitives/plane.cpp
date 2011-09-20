#include "plane.h"
//#include "math.h"
#include "../math_c.h"

Plane::Plane(Vector3 point, Vector3 norm, ColorRGB color, Material material)
    : point(point), norm(norm.Norm())
{
    this->color = color;
    this->material = material;
}

Vector3 Plane::Norm(Vector3 point)
{
    return norm;
}

Vector3 Plane::Trace(Ray ray)
{
    float sn = ray.dir.DotProduct(norm);

    if (sn == 0)
        return Vector3::Null();

    float dotPointNorm = point.DotProduct(norm);
    float t = (dotPointNorm - ray.from.DotProduct(norm)) / sn;

    if (t < EPS)
        return Vector3::Null();

    return ray.from + ray.dir * t;
}

ColorRGB Plane::Color(Vector3 point)
{
    return color;
}

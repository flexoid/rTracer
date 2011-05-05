#include "sphere.h"

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
    // Временная заглушка
    return Vector3(0,0,0);
}

ColorRGB Sphere::Color()
{
    return color;
}

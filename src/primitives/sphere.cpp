#include "sphere.h"
#include "math.h"
#include "../math_c.h"

Sphere::Sphere(Vector3 center, float radius, ColorRGB color, Material material)
    : center(center), radius(radius)
{
    this->color = color;
    this->material = material;
}

Vector3 Sphere::Norm(Vector3 point)
{
    return (point - center) / radius;
}

Vector3 Sphere::Trace(Ray ray)
{
    // Сдвигаем начало отсчета на вектор ray.from
    Vector3 ac=center-ray.from;
    float acs=0;
    // Вычисляем коэффиценты в квадратном уравнении пересечения сферы и прямой
    acs = ac.DotProduct(ray.dir);
    if (acs < 0)
        return Vector3(0,0,0);
    float sqrLength=ac.DotProduct(ac);
    // Вычисляем дискриминант, корни и находим точку пересечения
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

ColorRGB Sphere::Color(Vector3 point)
{
    return color;
}

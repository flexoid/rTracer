#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : Primitive
{
public:
    Sphere(Vector3 center, float radius, ColorRGB color);

    virtual Vector3 Norm(Vector3 point);
    virtual Vector3 Trace(Ray);
    virtual ColorRGB Color();
private:
    Vector3 center;
    float radius;
};

#endif // SPHERE_H

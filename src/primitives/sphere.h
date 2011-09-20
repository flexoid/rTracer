#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive
{
public:
    Sphere(Vector3 center, float radius, ColorRGB color, Material material);

    virtual Vector3 Norm(Vector3 point);
    virtual Vector3 Trace(Ray);
    virtual ColorRGB Color(Vector3 point);
private:
    Vector3 center;
    float radius;
};

#endif // SPHERE_H

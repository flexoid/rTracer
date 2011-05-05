#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include "iprimitive.h"

class Sphere : Primitive, IPrimitive
{
public:
    Sphere(Vector3 center, float radius);

    virtual Vector3 Norm(Vector3 point);
    virtual Vector3 Trace(Ray);
private:
    Vector3 center;
    float radius;
};

#endif // SPHERE_H

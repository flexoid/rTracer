#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../colorrgb.h"
#include "../material.h"
#include "../vector3.h"
#include "../ray.h"

class Primitive
{
public:
    virtual Vector3 Norm(Vector3) = 0;
    virtual Vector3 Trace(Ray) = 0;
    virtual ColorRGB Color(Vector3) = 0;
    Material material;
    float reflectC, refractC;
protected:
    ColorRGB color;
};

#endif // PRIMITIVE_H

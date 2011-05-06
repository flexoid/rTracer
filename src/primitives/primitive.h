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
    virtual ColorRGB Color() = 0;
protected:
    ColorRGB color;
    Material material;
};

#endif // PRIMITIVE_H

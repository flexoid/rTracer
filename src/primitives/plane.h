#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"

class Plane : public Primitive
{
public:
    Plane(Vector3 point, Vector3 norm, ColorRGB color, Material material);

    virtual Vector3 Norm(Vector3 point);
    virtual Vector3 Trace(Ray);
    virtual ColorRGB Color(Vector3 point);
private:
    Vector3 point;
    Vector3 norm;
};

#endif // PLANE_H

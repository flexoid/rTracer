#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray
{
public:
    Ray(Vector3 from, Vector3 dir) : from(from), dir(dir) {}
    Ray() {}
    Vector3 from;
    Vector3 dir;
};

#endif

#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray
{
public:
    Ray(Vector3 from, Vector3 dir, float power=1.0f) : from(from), dir(dir), power(power) {};
    Ray() {};
    Vector3 from;
    Vector3 dir;
    float power;
};

#endif

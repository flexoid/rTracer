#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"

class Light
{
public:
    Light(Vector3 InPos, float InPower) : pos(InPos), power(InPower) {}
    Vector3 pos;
    float power;
};

#endif // LIGHT_H

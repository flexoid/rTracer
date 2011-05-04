#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

#include "../vector3.h"
#include "../ray.h"

/**
  Интерфейс IPrimitive.
  Определяет базовые возможности для всех примитивов на сцене.
**/

class IPrimitive
{
public:
    virtual Vector3 Norm(Vector3) = 0;
    virtual Vector3 Trace(Ray) = 0;
};

#endif // IPRIMITIVE_H

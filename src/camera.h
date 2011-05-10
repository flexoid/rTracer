#ifndef CAMERA_H
#define CAMERA_H

#include "vector3.h"

class Camera
{
public:
    Camera(Vector3 from, Vector3 to, float w, float h)
    {
        SetParametrs(from,to,w,h);
    }
    Camera() : eye(Vector3::Null()), lt(Vector3::Null()), right(Vector3::Null()), down(Vector3::Null()) {}

    void SetParametrs(Vector3 from, Vector3 to, float w, float h)
    {
        Vector3 s = to - from;
        Vector3 r = s.CrossProduct(Vector3(0,0,1));
        Vector3 b = s.CrossProduct(r);
        lt = from + s + r*(-w/2.0f) + b*(-h/2.0f);
        right = w*r;
        down = h*b;
        eye = from;
    }

    Vector3 eye;
    Vector3 lt;
    Vector3 right;
    Vector3 down;
};

#endif // CAMERA_H

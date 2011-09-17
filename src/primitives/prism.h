#ifndef PRISM_H
#define PRISM_H

#include "primitive.h"

class Prism : public Primitive
{
public:
    Prism(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, Vector3 dir, float heigth, ColorRGB color, Material material);

    virtual Vector3 Norm(Vector3 point);
    virtual Vector3 Trace(Ray);
    virtual ColorRGB Color();
private:
    struct Face{
      Vector3 points[4];
      Vector3 norm;
      float D;
    };
    bool isInside(Vector3 point, Face face);
    Face faces[6];
    //Vector3 points[8];
};

#endif // PRISM_H

#ifndef TEXTUREHPLANE_H
#define TEXTUREHPLANE_H

#include "plane.h"

class TextureHPlane : public Plane
{
public:
    TextureHPlane(float height, Material material);
    ColorRGB Color(Vector3 point);
};

#endif // TEXTUREHPLANE_H

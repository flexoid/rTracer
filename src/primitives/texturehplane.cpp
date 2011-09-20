#include "texturehplane.h"
#include "math.h"

TextureHPlane::TextureHPlane(float height, Material material) : Plane(Vector3(0.0f,0.0f,height),Vector3(0.0f,0.0f,1.0f),
                                                                      ColorRGB(0,0,0),material) {}

ColorRGB TextureHPlane::Color(Vector3 point)
{

    if ( ( (int) trunc(point.x/2.0)&1) || ( (int) trunc(point.y/2.0)&1) )
        return ColorRGB(255,255,255);
    else
        return ColorRGB(0,0,0);

}

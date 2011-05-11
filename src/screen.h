#ifndef SCREEN_H
#define SCREEN_H

#include "raytracer.h"
#include "scene.h"
#include "pixel.h"
#include "camera.h"
#include "ray.h"

class Screen
{
 public:
    Screen(Camera*,Scene*,int,int);
    pixel GetPixel();
 private:
    int xmax, ymax;
    Screen();
    void SetNextPixel();
    Camera* cam;
    RayTracer rt;
    pixel currentPixel;
};

#endif

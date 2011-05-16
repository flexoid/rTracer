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
    enum Result { PixelDone, CellDone, AllDone };

    Screen(Camera* cam, Scene* scene, int x, int y, int cellSize = 100);
    Result GetPixel(pixel& pix);
 private:
    int xmax, ymax;
    Screen();
    Result SetNextPixel();
    Camera* cam;
    RayTracer rt;
    pixel currentPixel;
    int cellx, celly, cellSize;
};

#endif

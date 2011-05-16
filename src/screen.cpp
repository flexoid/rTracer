#include "screen.h"

Screen::Screen(Camera* cam, Scene* scene, int x, int y) : cam(cam), rt(RayTracer(scene)),
							  xmax(x),ymax(y){};

pixel Screen::GetPixel()
{
    pixel pix = currentPixel;
    Vector3 x = cam->right * (pix.x / float(xmax));
    Vector3 y = cam->down * (pix.y / float(ymax));
    Vector3 scr = cam->lt + (x + y);
    //pix.color = rt.Color(Ray(cam->eye, cam->lt + cam->right * pix.x * cam->width / xmax +
    //                          cam->down * pix.y * cam->height / ymax));
    pix.color = rt.Color(Ray(cam->eye, scr));
    SetNextPixel();
    return pix;
};

void Screen::SetNextPixel()
{
    ++currentPixel.y;
    if (currentPixel.y >= ymax)
    {
        currentPixel.y = 0;
        ++currentPixel.x;
    }
    if (currentPixel.x >= xmax)
    {
        currentPixel.x = 0;
    }
};


#include "screen.h"

Screen::Screen(Camera* cam, Scene* scene, int x, int y) : cam(cam), rt(RayTracer(scene)),
							  xmax(x),ymax(y){};

pixel Screen::GetPixel()
{
    pixel pix = currentPixel;
    pix.color = rt.Color(Ray(cam->eye, cam->lt+cam->right*pix.x*cam->width/xmax+
                              cam->down*pix.y*cam->height/ymax));
    SetNextPixel();
    return pix;
};

void Screen::SetNextPixel()
{
    currentPixel.y+=4;
    if (currentPixel.y >= ymax)
    {
        currentPixel.y = 0;
        currentPixel.x+=4;
    }
    if (currentPixel.x >= xmax)
    {
        currentPixel.x = 0;
    }
};


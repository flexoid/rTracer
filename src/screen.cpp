#include "screen.h"

Screen::Screen(Camera* cam, Scene* scene, int x, int y) : cam(cam), rt(RayTracer(scene)),
							  xmax(x),ymax(y){};

pixel Screen::GetPixel()
{
    pixel pix = GetNext();
    pix.color = rt.Color(Ray(cam->eye, cam->lt+cam->right*pix.x*cam->width/xmax+
			     cam->down*pix.y*cam->height/ymax));
    return pix;
};

pixel Screen::GetNext()
{
};


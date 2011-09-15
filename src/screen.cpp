#include "screen.h"

Screen::Screen(Camera* cam, Scene* scene, int x, int y, int cellSize)
    : cam(cam), rt(RayTracer(scene)), xmax(x), ymax(y), cellSize(cellSize)
{
    cellx = 1;
    celly = 1;
}

Screen::Result Screen::GetPixel(pixel& pix)
{
    pix = currentPixel;
    Vector3 x = cam->right * (pix.x / float(xmax));
    Vector3 y = cam->down * (pix.y / float(ymax));
    Vector3 scr = cam->lt + x + y;
    pix.color = rt.Color(Ray(cam->eye, scr));
    return SetNextPixel();
};

Screen::Result Screen::SetNextPixel()
{
    Result res = PixelDone;

    currentPixel.y++;
    if (currentPixel.y == celly * cellSize || currentPixel.y > ymax - 1)
    {
        currentPixel.y = (celly - 1) * cellSize;
        currentPixel.x++;
    }
    if (currentPixel.x == cellx * cellSize || currentPixel.x > xmax - 1)
    {
        celly++;
        res = CellDone;
        if (celly > (int)ceilf(ymax / (float)cellSize))
        {
            celly = 1;
            cellx++;
            if (cellx > (int)ceilf(xmax / (float)cellSize))
            {
                cellx = 1;
                res = AllDone;
            }
        }
        currentPixel.x = (cellx - 1) * cellSize;
        currentPixel.y = (celly - 1) * cellSize;
    }
    return res;
};


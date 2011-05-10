#ifndef PIXEL_H
#define PIXEL_H

#include "colorrgb.h"

struct pixel
{
    pixel(int x, int y, ColorRGB color) : x(x), y(y), color(color){};
    pixel() : x(0), y(0), color(ColorRGB::Null()){};

    static pixel Null(){return pixel();};

    ColorRGB color;
    int x,y;
};

#endif

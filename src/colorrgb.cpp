#include "colorrgb.h"

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b){};

ColorRGB::ColorRGB( ) : r(0), g(0), b(0){};

ColorRGB ColorRGB::operator+(const ColorRGB& c2) const
{
    return ColorRGB(r+c2.r, g+c2.g, b+c2.g);
};

ColorRGB ColorRGB::operator*(const float k) const
{
    return ColorRGB(k*r, k*g, k*b);
};

void ColorRGB::operator+=(const ColorRGB& c2)
{
    r+=c2.r;
    g+=c2.g;
    b+=c2.g;
};

ColorRGB ColorRGB::Null()
{
    return ColorRGB();
};

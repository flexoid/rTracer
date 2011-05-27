#include "colorrgb.h"

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b){};

ColorRGB::ColorRGB( ) : r(0), g(0), b(0){};

Uint16 min(Uint16 a, Uint16 b)
{
    return a<b?a:b;
};

ColorRGB ColorRGB::operator+(const ColorRGB& c2) const
{
    Uint32 rr = r + c2.r, gg = g + c2.g, bb = b + c2.b;
    if (rr > 255) {
        gg = min(gg + rr - 255, 255);
        bb = min(bb + rr - 255, 255);
        rr = 255;
    }
    if (gg > 255) {
        rr = min(rr + gg - 255, 255);
        bb = min(bb + gg - 255, 255);
        gg = 255;
    }
    if (bb > 255) {
        rr = min(rr + bb - 255, 255);
        gg = min(gg + bb - 255, 255);
        bb = 255;
    }
    return ColorRGB(rr, gg, bb);
 };

ColorRGB ColorRGB::operator*(const float k) const
{
    Uint32 rr = r * k, gg = g * k, bb = b * k;
    if (rr > 255) {
        gg = min(gg + rr - 255, 255);
        bb = min(bb + rr - 255, 255);
        rr = 255;
    }
    if (gg > 255) {
        rr = min(rr + gg - 255, 255);
        bb = min(bb + gg - 255, 255);
        gg = 255;
    }
    if (bb > 255) {
        rr = min(rr + bb - 255, 255);
        gg = min(gg + bb - 255, 255);
        bb = 255;
    }
    return ColorRGB(rr, gg, bb);
};

void ColorRGB::operator+=(const ColorRGB& c2)
{
    *this = *this + c2;
};

ColorRGB ColorRGB::Null()
{
    return ColorRGB();
};

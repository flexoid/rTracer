#include "colorrgb.h"

ColorRGB::ColorRGB(Uint8 r, Uint8 g, Uint8 b) : r(r), g(g), b(b){};

ColorRGB::ColorRGB( ) : r(0), g(0), b(0){};

Uint16 min(Uint16 a, Uint16 b)
{
    return a<b?a:b;
};

ColorRGB ColorRGB::operator+(const ColorRGB& c2) const
{
    Uint32 rr=(Uint32) r+(Uint32) c2.r, gg=(Uint32) g+(Uint32) c2.g, bb=(Uint32) b+(Uint32) c2.b;
    if (rr>255)
        { gg=min(0+gg+rr-255,255); bb=min(0+bb+rr-255,255); rr=255;}
    if (gg>255)
        { rr=min(0+rr+gg-255,255); bb=min(0+bb+gg-255,255); gg=255;}
    if (bb>255)
        { rr=min(0+rr+bb-255,255); gg=min(0+gg+bb-255,255); bb=255;}
    return ColorRGB(rr,gg,bb);
 };

ColorRGB ColorRGB::operator*(const float k) const
{
    Uint32 rr=(Uint32) r*k, gg=(Uint32) g*k, bb=(Uint32) b*k;
    if (rr>255)
        { gg=min(0+gg+rr-255,255); bb=min(0+bb+rr-255,255); rr=255;}
    if (gg>255)
        {rr=min(0+rr+gg-255,255); bb=min(0+bb+gg-255,255); gg=255;}
    if (bb>255)
        { rr=min(0+rr+bb-255,255); gg=min(0+gg+bb-255,255); bb=255;}
    return ColorRGB(rr,gg,bb);
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

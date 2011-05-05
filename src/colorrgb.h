#ifndef COLORRGB_H
#define COLORRGB_H

class ColorRGB
{
public:
    ColorRGB(float InR, float InG, float InB) : r(InR), g(InG), b(InB) {}
    ColorRGB( ) : r(0), g(0), b(0) {}
    float r, g, b;
};

#endif // COLORRGB_H

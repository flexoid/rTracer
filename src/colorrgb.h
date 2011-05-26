#ifndef COLORRGB_H
#define COLORRGB_H

#include <SDL/SDL.h>

class ColorRGB
{
public:
    ColorRGB(Uint8, Uint8, Uint8);
    ColorRGB();

    ColorRGB operator*(const float) const;
    ColorRGB operator+(const ColorRGB&) const;
    void operator+=(const ColorRGB&);

    inline bool operator== (const ColorRGB& color) const
    {
        return (r == color.r && g == color.g && b == color.b);
    }

    bool operator!= (const ColorRGB& color) const
    {
        return !(*this == color);
    }

    static ColorRGB Null();

    Uint8 r, g, b;
};

#endif // COLORRGB_H

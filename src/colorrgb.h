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

  static ColorRGB Null();

  Uint8 r, g, b;
};

#endif // COLORRGB_H

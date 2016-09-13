//
// Created by Eddie on 12-Sep-16.
//

#include "../headers/RGB565.h"

namespace Ramp
{
  RGB565::RGB565()
          : r(0),
            g(0),
            b(0) {}

  RGB565::RGB565(const unsigned short i)
          : r(static_cast<unsigned short>((i >> 11) & 0b11111)),
            g(static_cast<unsigned short>((i >> 5) & 0b111111)),
            b(static_cast<unsigned short>(i & 0b11111)) {}

  unsigned short RGB565::to_ushort()
  {
    return b + (g << 5) + (r << 11);
  }

  bool RGB565::operator==(const RGB565 &rhs) const
  {
    return r == rhs.r &&
           g == rhs.g &&
           b == rhs.b;
  }

  bool RGB565::operator!=(const RGB565 &rhs) const
  {
    return !(rhs == *this);
  }


}
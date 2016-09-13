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
          : r((i >> 11) & 0b11111),
            g((i >> 5) & 0b111111),
            b(i & 0b11111) {}

  unsigned short RGB565::to_ushort()
  {
    unsigned short output = 0;
    output += r << 11;
    output += g << 5;
    output += b;
    return output;
  }


}
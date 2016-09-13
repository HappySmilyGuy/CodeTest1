//
// Created by Eddie on 12-Sep-16.
//

#ifndef RAMP_RGB565_H
#define RAMP_RGB565_H

namespace Ramp
{
  class RGB565
  {
  public:
    RGB565();
    RGB565(const unsigned short i);
    unsigned short to_ushort();

    unsigned short r, g, b;
  };
}

#endif //RAMP_RGB565_H

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
    RGB565(const unsigned short rgb565);
    RGB565(const unsigned short r,
           const unsigned short g,
           const unsigned short b);
    unsigned short to_ushort() const;
    bool operator==(const RGB565 &rhs) const;
    bool operator!=(const RGB565 &rhs) const;

    unsigned short r, g, b;
  };
}

#endif //RAMP_RGB565_H

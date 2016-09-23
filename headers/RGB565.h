#ifndef RAMP_RGB565_H
#define RAMP_RGB565_H

namespace Ramp
{
  // class to represent a colour as 5bits to represent the red component, 6bits for the green, 5bits for blue
  class RGB565
  {
  public:
    RGB565();
    RGB565(unsigned short rgb565);
    RGB565(unsigned short red,
           unsigned short green,
           unsigned short blue);

    unsigned short to_ushort() const;
    bool operator==(const RGB565 &rhs) const;
    bool operator!=(const RGB565 &rhs) const;
    unsigned short get_r() const;
    unsigned short get_g() const;
    unsigned short get_b() const;

  private:
    unsigned short r_, g_, b_;
  };
}

#endif //RAMP_RGB565_H

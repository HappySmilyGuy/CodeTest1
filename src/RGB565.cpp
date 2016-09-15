#include "../headers/RGB565.h"

namespace Ramp
{
  RGB565::RGB565()
          : r_(0),
            g_(0),
            b_(0) {}

  RGB565::RGB565(const unsigned short rgb565)
          : r_(static_cast<unsigned short>((rgb565 >> 11) & 0b11111)),
            g_(static_cast<unsigned short>((rgb565 >> 5) & 0b111111)),
            b_(static_cast<unsigned short>(rgb565 & 0b11111)) {}

  RGB565::RGB565(const unsigned short red,
                 const unsigned short green,
                 const unsigned short blue)
          : r_(static_cast<unsigned short>(red & 0b11111)),
            g_(static_cast<unsigned short>(green & 0b111111)),
            b_(static_cast<unsigned short>(blue & 0b11111)) {}

  unsigned short RGB565::to_ushort() const
  {
    return b_ + (g_ << 5) + (r_ << 11);
  }

  bool RGB565::operator==(const RGB565 &rhs) const
  {
    return r_ == rhs.r_ &&
           g_ == rhs.g_ &&
           b_ == rhs.b_;
  }

  bool RGB565::operator!=(const RGB565 &rhs) const
  {
    return !(rhs == *this);
  }

  unsigned short RGB565::get_r() const
  {
    return r_;
  }

  unsigned short RGB565::get_g() const
  {
    return g_;
  }

  unsigned short RGB565::get_b() const
  {
    return b_;
  }
}
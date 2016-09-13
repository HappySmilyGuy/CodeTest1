//
// Created by Eddie on 13-Sep-16.
//

#include "RGB565_tests.h"
#include <cassert>
#include "../headers/RGB565.h"
#include "../headers/constants.h"

namespace Ramp
{
  namespace Test
  {
    namespace RGB565Tests
    {
      void test_default_constructor()
      {
        RGB565 colour;
        assert(colour.r == 0);
        assert(colour.g == 0);
        assert(colour.b == 0);
      }

      void test_integer_constructor()
      {
        unsigned short us = 3 + (5 << 5) + (8 << 11);
        RGB565 colour = RGB565(us);
        assert(colour.r == 8);
        assert(colour.g == 5);
        assert(colour.b == 3);

        colour = RGB565(0);
        assert(colour.r == 0);
        assert(colour.g == 0);
        assert(colour.b == 0);

        colour = RGB565(Constants::MAX_COLOUR_VAL);
        assert(colour.r == 0b11111);
        assert(colour.g == 0b111111);
        assert(colour.b == 0b11111);
      }

      void test_to_ushort()
      {
        RGB565 colour = RGB565(0);
        assert(colour.to_ushort() == (unsigned short) 0);

        colour = RGB565(Constants::MAX_COLOUR_VAL);
        assert(colour.to_ushort() == Constants::MAX_COLOUR_VAL);
      }

      void test_all()
      {
        test_default_constructor();
        test_integer_constructor();
        test_to_ushort();
      }
    }
  }
}

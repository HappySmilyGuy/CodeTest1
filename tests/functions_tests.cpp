//
// Created by Eddie on 13-Sep-16.
//

#include "functions_tests.h"
#include <cassert>
#include "../headers/functions.h"

namespace Ramp
{
  namespace Test
  {
    namespace FunctionsTests
    {
      void test_set_conrner_values()
      {
        Ramp::RGB565 tl, tr, bl, br;
        int argc = 6;
        char *argv[] = {(char *) "ramp.exe", (char *) "display", (char *) "0", (char *) "2", (char *) "3", (char *) "4",
                        NULL};
        Ramp::set_corner_values(argc, argv, tl, tr, bl, br);
        assert(tl.b == 0);
        assert(tr.b == 2);
        assert(bl.b == 3);
        assert(br.b == 4);
      }

      void test_checks_args()
      {
        std::string errors;
        bool show_help = false;
        int argc = 6;
        char *argv[] = {(char *) "ramp.exe", (char *) "display", (char *) "0", (char *) "0", (char *) "0", (char *) "0",
                        NULL};
        Display d;
        assert(Ramp::checks_args(argc, argv, d, show_help, errors));
        assert(!show_help);
        assert(errors == "");
      }

      void test_all()
      {
        test_set_conrner_values();
        test_checks_args();
      }
    }
  }
}


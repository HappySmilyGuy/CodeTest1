//
// Created by Eddie on 12-Sep-16.
//

#ifndef RAMP_FUNCTIONS_H
#define RAMP_FUNCTIONS_H

#include <vector>
#include <string>
#include "Display.h"
#include "RGB565.h"

namespace Ramp
{
  std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
                                                         const RGB565 &br, const unsigned int width,
                                                         const unsigned int height);

  // returns false if not passed input checks:
  // input checks:
  //    - can connect to device
  //    - correct number of inputs
  //    - the value of each input is an integer between 0 and 0xffff
  bool checks_args(int argc, char *argv[], Display &d, bool &show_help, std::string &errors);

  void display_rows(std::vector<std::vector<RGB565>> rows, Display &display);

  void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br);
}

#endif //RAMP_FUNCTIONS_H

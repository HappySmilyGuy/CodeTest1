#ifndef RAMP_FUNCTIONS_H
#define RAMP_FUNCTIONS_H

#include <vector>
#include <string>
#include "Display.h"
#include "RGB565.h"

namespace Ramp
{
  // returns all the pixels in a width by height array (as a vector of rows) with
  // @tl @tr @bl and @br becoming the top left, top right, bottom left and bottom right pixels respectively
  // and all the other pixels bing an even spread of linear progression between those values.
  std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
                                                         const RGB565 &br, const unsigned int width,
                                                         const unsigned int height);

  // returns false if not passed input checks:
  // input checks:
  //    - can connect to device
  //    - correct number of inputs
  //    - the value of each input is an integer between 0 and 0xffff
  // returns true if there is a request for help or valid input args for processing.
  // if this returns false and @show_help is false, an error string to suggest the problem.
  bool checks_args(int argc, char *argv[], Display &d, bool &show_help, std::string &errors);

  // outputs @rows to @display.
  void display_rows(Display &display, std::vector<std::vector<RGB565>> rows);

  // Sets tl, tr, bl and br RGB565 values from the 3rd to 6th argv values respectively.
  // If bl and br default to tl and tr respectively if there aren't that many argv elements.
  void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br);
}

#endif //RAMP_FUNCTIONS_H

#include <iostream>
#include <vector>
#include "../headers/constants.h"
#include "../headers/Display.h"
#include "../headers/functions.h"

int main(int argc, char *argv[])
{
  Display display;

  bool display_help = false;
  std::string errors;

  if (!Ramp::checks_args(argc, argv, display, display_help, errors))
  {
    std::cerr << errors << std::endl;
    return -1;
  }
  if (display_help)
  {
    std::cout << Ramp::Constants::HELP_TEXT << std::endl;
    return 1;
  }

  Ramp::RGB565 tl, tr, bl, br;
  Ramp::set_corner_values(argc, argv, tl, tr, bl, br);

  int width(0), height(0);
  display.get_size(width, height);
  std::vector<std::vector<Ramp::RGB565>> rows = Ramp::calculate_ramped_rows(tl, tr, bl, br, width, height);

  Ramp::display_rows(rows, display);
  return 0;
}
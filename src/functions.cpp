#include "../headers/functions.h"
#include "../headers/constants.h"

namespace Ramp
{
  namespace
  {
    void spread_out(double &first, double &last)
    {
      if (first < last)
      {
        first -= 0.5;
        last += 0.5;
      }
      else if (first > last)
      {
        first += 0.5;
        last -= 0.5;
      }
    }

    bool check_colour_input(const std::string &input_colour_str)
    {
      if (input_colour_str[0] < '0' || input_colour_str[0] > '9')
      {
        return false;
      }
      std::string::size_type st = 0;
      int colour_val = std::stoi(input_colour_str, &st, 0);
      return (input_colour_str.length() == st
              && colour_val >= 0
              && colour_val <= Ramp::Constants::MAX_COLOUR_VAL);
    }

    // creates a smooth progression between @first and @last RGB values across
    std::vector<RGB565> calculate_ramp_line(const RGB565 &first, const RGB565 &last, const int no_of_pixels)
    {
      double first_r = static_cast<double>(first.get_r());
      double first_g = static_cast<double>(first.get_g());
      double first_b = static_cast<double>(first.get_b());
      double last_r = static_cast<double>(last.get_r());
      double last_g = static_cast<double>(last.get_g());
      double last_b = static_cast<double>(last.get_b());
      spread_out(first_r, last_r);
      spread_out(first_g, last_g);
      spread_out(first_b, last_b);

      int max_pixel_val = no_of_pixels - 1;

      std::vector<RGB565> output;
      for (double i = 0; i < no_of_pixels; ++i)
      {
        RGB565 pixel;
        if (i == 0)
        {
          pixel = first;
        }
        else if (i == max_pixel_val)
        {
          pixel = last;
        }
        else
        {
          pixel = RGB565(static_cast<unsigned short>((first_r * (((max_pixel_val - i) / max_pixel_val)) +
                                                      (last_r * ((i / max_pixel_val)))) + 0.5),
                         static_cast<unsigned short>((first_g * (((max_pixel_val - i) / max_pixel_val)) +
                                                      (last_g * ((i / max_pixel_val)))) + 0.5),
                         static_cast<unsigned short>((first_b * (((max_pixel_val - i) / max_pixel_val)) +
                                                      (last_b * ((i / max_pixel_val)))) + 0.5));
        }
        output.push_back(pixel);
      }
      return output;
    }
  }

  std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
                                                         const RGB565 &br, const unsigned int width,
                                                         const unsigned int height)
  {
    std::vector<RGB565> left_column = calculate_ramp_line(tl, bl, height);
    std::vector<RGB565> right_column = calculate_ramp_line(tr, br, height);

    std::vector<std::vector<RGB565>> output;
    for (unsigned int y = 0; y < height; ++y)
    {
      std::vector<RGB565> row = calculate_ramp_line(left_column[y], right_column[y], width);
      if (row.size() > 0)
      {
        output.push_back(calculate_ramp_line(left_column[y], right_column[y], width));
      }
    }
    return output;
  }

  void display_rows(Display &display, std::vector<std::vector<RGB565>> rows)
  {
    int x = 0, y = 0;
    for (std::vector<std::vector<RGB565>>::iterator rows_it = rows.begin(); rows_it != rows.end(); ++rows_it)
    {
      unsigned int width = static_cast<unsigned int>(rows_it->size());
      unsigned short pixels[width] = {};
      x = 0;
      for (std::vector<RGB565>::iterator pixels_it = rows_it->begin(); pixels_it != rows_it->end(); ++pixels_it)
      {
        pixels[x] = pixels_it->to_ushort();
        ++x;
      }
      display.draw_raster(0, y, pixels, width);
      ++y;
    }
  }

  void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br)
  {
    tl = RGB565(static_cast<unsigned short>(std::stoi(argv[2], 0, 0)));
    tr = RGB565(static_cast<unsigned short>(std::stoi(argv[3], 0, 0)));
    if (argc > 4)
    {
      bl = RGB565(static_cast<unsigned short>(std::stoi(argv[4], 0, 0)));
    }
    else
    {
      bl = tl;
    }
    if (argc > 5)
    {
      br = RGB565(static_cast<unsigned short>(std::stoi(argv[5], 0, 0)));
    }
    else
    {
      br = tr;
    }
  }

  bool checks_args(int argc, char *argv[], Display &d, bool &show_help, std::string &errors)
  {
    bool output = true;
    show_help = false;
    switch (argc)
    {
      case 6 :
      case 5 :
      case 4 :
        if (!d.connect(argv[2]))
        {
          errors += Ramp::Constants::DEVICE_CONNECTION_FAILURE_MSG + " " + argv[1] + ".\n";
          output = false;
          break;
        }
        for (int i = 2; i < argc; ++i)
        {
          if (!check_colour_input(argv[i]))
          {
            std::string new_error = Ramp::Constants::INT_FORMAT_ERROR_MSG;
            errors += new_error.insert(Ramp::Constants::INT_FORMAT_ERROR_MSG_INPUT_POS, std::string(argv[i])) + "\n";
            output = false;
            break;
          }
        }
        break;
      case 3 :
      case 2 :
        if (argv[1][0] == 'h')
        {
          show_help = true;
          return true;
        }
      case 1 :errors += Ramp::Constants::TOO_FEW_CMD_ARGS_MSG + "\n";
        output = false;
        break;

      default:errors += Ramp::Constants::TOO_MANY_CMD_ARGS_MSG + "\n";
        output = false;
        break;
    }

    if (!output)
    {
      errors += Ramp::Constants::HELP_SUGGESTION_MSG + "\n";
    }
    return output;
  }
}
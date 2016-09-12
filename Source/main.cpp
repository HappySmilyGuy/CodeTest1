#include <iostream>
#include <vector>
#include "../Headers/constants.h"
#include "../Headers/Display.h"

namespace
{

    struct RGB565
    {
        int r = 0;
        int g = 0;
        int b = 0;
    };

    RGB565 int_to_RGB565(int i)
    {
      RGB565 output;
      output.b = i & 0b11111;
      output.g = (i >> 5) & 0b111111;
      output.r = (i >> 11) & 0b11111;
      return output;
    }

    unsigned short RGB565_to_ushort(RGB565 in)
    {
      unsigned short output = 0;
      output += in.r << 11;
      output += in.g << 5;
      output += in.b;
      return output;
    }

    void spread_out(double &first, double &last)
    {
      if (first < last)
      {
        first -= 0.5;
        last += 0.5;
      } else if (first > last)
      {
        first += 0.5;
        last -= 0.5;
      }
    }

    std::vector<RGB565> calculate_ramp_line(const RGB565 &first, const RGB565 &last, const int no_of_pixels)
    {
      double first_r = static_cast<double>(first.r);
      double first_g = static_cast<double>(first.g);
      double first_b = static_cast<double>(first.b);
      double last_r = static_cast<double>(last.r);
      double last_g = static_cast<double>(last.g);
      double last_b = static_cast<double>(last.b);
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
        } else if (i == max_pixel_val)
        {
          pixel = last;
        } else
        {
          pixel.r = static_cast<int>(
                  (first_r * (((max_pixel_val - i) / max_pixel_val)) + (last_r * ((i / max_pixel_val)))) + 0.5);
          pixel.g = static_cast<int>(
                  (first_g * (((max_pixel_val - i) / max_pixel_val)) + (last_g * ((i / max_pixel_val)))) + 0.5);
          pixel.b = static_cast<int>(
                  (first_b * (((max_pixel_val - i) / max_pixel_val)) + (last_b * ((i / max_pixel_val)))) + 0.5);
        }
        output.push_back(pixel);
      }
      return output;
    }

    void display_rows(std::vector<std::vector<RGB565>> rows, Display &display)
    {
      int x = 0, y = 0;
      for (std::vector<std::vector<RGB565>>::iterator rows_it = rows.begin(); rows_it != rows.end(); ++rows_it)
      {
        unsigned int width = static_cast<unsigned int>(rows_it->size());
        unsigned short pixels[width] = {};
        x = 0;
        for (std::vector<RGB565>::iterator pixels_it = rows_it->begin(); pixels_it != rows_it->end(); ++pixels_it)
        {
          pixels[x] = RGB565_to_ushort(*pixels_it);
          ++x;
        }
        display.draw_raster(0, y, pixels, width);
        ++y;
      }
    }

    std::vector<std::vector<RGB565>> calculate_ramped_rows(const RGB565 &tl, const RGB565 &tr, const RGB565 &bl,
                                                           const RGB565 &br, const int width, const int height)
    {
      std::vector<RGB565> left_column = calculate_ramp_line(tl, bl, height);
      std::vector<RGB565> right_column = calculate_ramp_line(tr, br, height);

      std::vector<std::vector<RGB565>> output;
      for (int y = 0; y < height; ++y)
      {
        output.push_back(calculate_ramp_line(left_column[y], right_column[y], width));
      }
      return output;
    }

    inline void set_corner_values(int argc, char *argv[], RGB565 &tl, RGB565 &tr, RGB565 &bl, RGB565 &br)
    {
      tl = int_to_RGB565(std::stoi(argv[2]));
      tr = int_to_RGB565(std::stoi(argv[3]));
      if (argc > 4)
      {
        bl = int_to_RGB565(std::stoi(argv[4]));
      } else
      {
        bl = tl;
      }
      if (argc > 5)
      {
        br = int_to_RGB565(std::stoi(argv[5]));
      } else
      {
        br = tr;
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
              && colour_val <= Ramp::Constants::MAX_INT);
    }

    // returns false if not passed input checks:
    // input checks:
    //    - can connect to device
    //    - correct number of inputs
    //    - the value of each input is an integer between 0 and 0xffff
    bool checks_args(int argc, char *argv[], Display &d)
    {
      bool output = true;
      switch (argc)
      {
        case 6 :
        case 5 :
        case 4 :
          if (!d.connect(argv[2]))
          {
            std::cerr << Ramp::Constants::DEVICE_CONNECTION_FAILURE_MSG << " " << argv[1] << "." << std::endl;
            output = false;
            break;
          }
          for (int i = 2; i < argc; ++i)
          {
            if (!check_colour_input(argv[i]))
            {
              std::cerr << "Input error at \"" << argv[i] << "\":\n"
                        << Ramp::Constants::INT_FORMAT_ERROR_MSG << std::endl;
              output = false;
              break;
            }
          }
          break;
        case 3 :
        case 2 :
          if (argv[1][0] == 'h')
          {
            std::cout << Ramp::Constants::HELP_TEXT << std::endl;
            // purposeful short circuit
            return false;
          }
        case 1 :
          std::cerr << "Insufficient commandline arguments." << std::endl;
          output = false;
          break;

        default:
          std::cerr << "Too many commandline arguments." << std::endl;
          output = false;
          break;
      }

      if (!output)
      {
        std::cout << "Run as \"" << Ramp::Constants::EXE_NAME << " help\" for help." << std::endl;
      }
      return output;
    }

}

int main(int argc, char *argv[])
{
  Display display;
  if (!checks_args(argc, argv, display))
  {
    return -1;
  }
  RGB565 tl, tr, bl, br;
  set_corner_values(argc, argv, tl, tr, bl, br);

  int width(0), height(0);
  display.get_size(width, height);
  std::vector<std::vector<RGB565>> rows = calculate_ramped_rows(tl, tr, bl, br, width, height);

  display_rows(rows, display);
  return 0;
}
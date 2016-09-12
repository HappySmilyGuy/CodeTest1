//
// Created by Eddie on 08-Sep-16.
//

#include <cstdio>
#include <memory>
#include <cstring>
#include "../Headers/Display.h"

#define W 16
#define H 9
static unsigned short frame_buffer[W * H];

Display::Display()
{
  std::memset(frame_buffer, 0, sizeof(frame_buffer));
}

Display::~Display()
{
  unsigned short *pix = frame_buffer;
  for (int y = 0; y < H; y++)
  {
    for (int x = 0; x < W; x++)
    {
      if (x > 0)
      {
        printf(" ");
      }
      printf("%04X", *pix++);
    }
    printf("\n");
  }
}

bool Display::connect(const char *display_name)
{
  return true;
}

void Display::get_size(int &width, int &height)
{
  width = W;
  height = H;
}

void Display::draw_raster(int x, int y,
                          const unsigned short *pixels, int width)
{
  std::memcpy(&frame_buffer[y * W + x], pixels, width * sizeof(unsigned short));
}

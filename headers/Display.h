#ifndef RAMP_DISPLAY_H
#define RAMP_DISPLAY_H

class Display
{
public:
  Display();
  ~Display();
  bool connect(const char *Display_name);
  void get_size(int &width, int &height);
  void draw_raster(int x, int y,
                     const unsigned short *pixels, int width);
};

#endif //RAMP_DISPLAY_H

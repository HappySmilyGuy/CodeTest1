//
// Created by Eddie on 08-Sep-16.
//

#ifndef COLOURCHART_DISPLAY_H
#define COLOURCHART_DISPLAY_H

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

#endif //COLOURCHART_DISPLAY_H

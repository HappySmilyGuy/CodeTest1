run_ramper.exe

Brief description of the program's function:
Taking a display and 2-4 pixel values the program outputs a 2D array of pixels to the input display, creating a ramp of
colour values smoothly connecting each input pixel value.

For a more detailed description of the function of this program see the document "NR-110554-TC-4A-Coding Test.doc".

The executable is stored in bin/Release.

Brief internal description:
The output pixel values are calculated by:
 1. Creating a smooth progression between the top and bottom on the far left pixels and on the far right.
 2. Creating a smooth transition over each row, connecting the calculated furthest left and furthest right pixel on that row.
Then output to the display.

Credits:
test/libs/ folder is written under Google.
headers/Display.h, src/Display.cpp and NR-110554-TC-4A-Coding Test.doc are written under DisplayLink.
The rest of the code is written by Eddie Latimer, September 2016.